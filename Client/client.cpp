#include <iostream>
#include <mutex>

#include <Common/message.hpp>
#include <Controller/ControllerFactory.hpp>
#include <Interface/InterfaceFactory.hpp>
#include <KeyCatchingRoutine/KeyCatchingRoutineFactory.hpp>
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

        auto server_proxy =
            Client::ServerProxy::ServerProxyFactory::createInstance(argv[1], argv[2]);
        auto key_catching_routine =
            Client::KeyCatchingRoutine::KeyCatchingRoutineFactory::createInstance();
        auto interface = Client::Interface::InterfaceFactory::createInstance();
        auto controller =
            Client::Controller::ControllerFactory::createInstance(server_proxy, interface);

        auto on_action_callback = [&mutex](EAction action, const message_t& msg) {
            std::lock_guard<std::mutex> lock(mutex);

            std::cout.write(msg.body, msg.header.size);
            std::cout << "\n";
        };
        auto on_key_pressed_callback = [&controller](char c) { controller->processInput(c); };

        server_proxy->setOnActionCallback(on_action_callback);

        key_catching_routine->setOnKeyPressedCallback(on_key_pressed_callback);
        key_catching_routine->start();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}