//
// chat_server.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <mutex>

#include <ClientProxy/ClientProxyFactory.hpp>
#include <Common/message.hpp>

using boost::asio::ip::tcp;

namespace {
    boost::asio::mutable_buffers_1 toBuffer(message_t& message)
    {
        return boost::asio::buffer(toCharPtr(message), c_message_size);
    }
}

//----------------------------------------------------------------------

typedef std::deque<message_t> chat_message_queue;

//----------------------------------------------------------------------

class chat_participant
{
public:
  virtual ~chat_participant() {}
  virtual void deliver(const message_t& msg) = 0;
  virtual int getId() = 0;
};

typedef boost::shared_ptr<chat_participant> chat_participant_ptr;

//----------------------------------------------------------------------

class chat_room
{
public:
  void join(chat_participant_ptr participant)
  {
    participants_.insert(participant);
    //std::for_each(recent_msgs_.begin(), recent_msgs_.end(),
    //    boost::bind(&chat_participant::deliver, participant, _1));
  }

  void leave(chat_participant_ptr participant)
  {
    participants_.erase(participant);
  }

  void deliver(const message_t& msg)
  {
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
      recent_msgs_.pop_front();

    for (auto& participant : participants_)
    {
        participant->deliver(msg);
    }
  }

private:
  std::set<chat_participant_ptr> participants_;
  enum { max_recent_msgs = 100 };
  chat_message_queue recent_msgs_;
};

//----------------------------------------------------------------------

class chat_session
  : public chat_participant,
    public boost::enable_shared_from_this<chat_session>
{
public:
  chat_session(const Server::ClientProxy::ClientProxyPtr& proxy_ptr, chat_room& room, int id)
    : m_client_proxy(proxy_ptr)
    , id_(id)
  {
  }

  virtual int getId() final
  {
      return id_;
  }

  void deliver(const message_t& msg)
  {
      std::lock_guard<std::mutex> lock(mutex);

      m_client_proxy->sendMessage(msg);
  }

private:
  Server::ClientProxy::ClientProxyPtr m_client_proxy;
  message_t read_msg_;
  std::mutex mutex;
  chat_message_queue write_msgs_;
  int id_;
};

typedef boost::shared_ptr<chat_session> chat_session_ptr;

//----------------------------------------------------------------------

class chat_server
{
public:
  chat_server(boost::asio::io_service& io_service,
      const tcp::endpoint& endpoint)
    : io_service_(io_service)
    , acceptor_(io_service, endpoint)
    , pending_socket(io_service_)
  {
    acceptor_.async_accept(pending_socket,
        boost::bind(&chat_server::handle_accept, this, boost::asio::placeholders::error));
  }

  void handle_accept(const boost::system::error_code& error)
  {
    if (!error)
    {
      std::cout << "New connection" << std::endl;
      Server::ClientProxy::ClientProxyPtr client_proxy_ptr
        = Server::ClientProxy::ClientProxyFactory::createInstance(std::move(pending_socket));

      chat_session_ptr new_session(new chat_session(client_proxy_ptr, room_, id++));

      pending_socket = tcp::socket(io_service_);

      room_.join(new_session);

        auto on_action_callback = [this](EAction action, const message_t& msg)
        {
            room_.deliver(msg);
        };

      client_proxy_ptr->setOnActionCallback(on_action_callback);

      acceptor_.async_accept(pending_socket,
          boost::bind(&chat_server::handle_accept, this, boost::asio::placeholders::error));
    }
  }

private:
  boost::asio::io_service& io_service_;
  tcp::socket pending_socket;
  tcp::acceptor acceptor_;
  chat_room room_;
  int id = 0;
};

typedef boost::shared_ptr<chat_server> chat_server_ptr;
typedef std::list<chat_server_ptr> chat_server_list;

//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  try
  {
    if (argc < 2)
    {
      std::cerr << "Usage: chat_server <port> [<port> ...]\n";
      return 1;
    }

    boost::asio::io_service io_service;

    chat_server_list servers;
    for (int i = 1; i < argc; ++i)
    {
      using namespace std; // For atoi.
      tcp::endpoint endpoint(tcp::v4(), atoi(argv[i]));
      chat_server_ptr server(new chat_server(io_service, endpoint));
      servers.push_back(server);
    }

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}