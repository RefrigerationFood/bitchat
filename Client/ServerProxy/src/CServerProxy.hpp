#pragma once

#include <boost/asio.hpp>

#include <mutex>
#include <thread>

#include <Common/message.hpp>
#include <ServerProxy/IServerProxy.hpp>

namespace Client {
namespace ServerProxy {
using boost::asio::ip::tcp;

class CServerProxy : public IServerProxy
{
public: // methods
    CServerProxy(const std::string& host, const std::string& port);
    ~CServerProxy() final;
    void sendMessage(const message_t& msg) final;
    void setOnActionCallback(ActionCallback callback) final;

private: // methods
    void handleConnect(const boost::system::error_code& error);
    void handleRead(const boost::system::error_code& error);
    void handleWrite(const boost::system::error_code& error);

private: // fields
    ActionCallback m_action_callback;
    boost::asio::io_service m_io_service;
    tcp::resolver m_resolver;
    tcp::resolver::query m_query;
    tcp::resolver::iterator m_endpoint_iterator;
    tcp::socket m_socket;
    message_t m_tmp_message;
    std::mutex m_mutex;
    std::thread m_io_service_run_thread;
};
} // namespace ServerProxy
} // namespace Client