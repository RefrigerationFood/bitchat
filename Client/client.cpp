//
// chat_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <mutex>

#include <Common/message.hpp>
#include <ServerProxy/ServerProxyFactory.hpp>

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: chat_client <host> <port>\n";
      return 1;
    }

    std::mutex mutex;
    auto on_action_callback = [&mutex](EAction action, const message_t& msg)
    {
        std::lock_guard<std::mutex> lock(mutex);

        std::cout.write(msg.body, msg.header.size);
        std::cout << "\n";
    };

    Client::ServerProxy::ServerProxyPtr server_proxy =
        Client::ServerProxy::ServerProxyFactory::createInstance(argv[1], argv[2]);

    server_proxy->setOnActionCallback(on_action_callback);

    char line[c_max_body_size + 1];
    while (std::cin.getline(line, c_max_body_size + 1))
    {
      using namespace std; // For strlen and memcpy.
      message_t msg;
      msg.header.size = strlen(line);
      msg.header.action = EAction::Message;
      memcpy(msg.body, line, msg.header.size);
      server_proxy->sendMessage(msg);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}