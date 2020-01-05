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

        auto server_proxy =
            Client::ServerProxy::ServerProxyFactory::createInstance(argv[1], argv[2]);
        auto key_catching_routine =
            Client::KeyCatchingRoutine::KeyCatchingRoutineFactory::createInstance();
        auto interface = Client::Interface::InterfaceFactory::createInstance();
        auto controller = Client::Controller::ControllerFactory::createInstance(
            server_proxy, interface, key_catching_routine);

        key_catching_routine->start();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}