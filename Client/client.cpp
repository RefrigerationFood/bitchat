#include <iostream>
#include <mutex>

#include <Controller/ControllerFactory.hpp>
#include <Interface/InterfaceFactory.hpp>
#include <KeyCatchingRoutine/KeyCatchingRoutineFactory.hpp>
#include <ServerProxy/ServerProxyFactory.hpp>
#include <SettingsManager/SettingsManagerFactory.hpp>
#include <ncurses.h>

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 4)
        {
            std::cerr << "Usage: chat_client <host> <port> <name>\n";
            return 1;
        }

        initscr();

        auto settings_manager = Client::SettingsManager::SettingsManagerFactory::createInstance();
        settings_manager->getClientNameAttribute().setValue(argv[3]);

        auto server_proxy =
            Client::ServerProxy::ServerProxyFactory::createInstance(argv[1], argv[2]);
        auto key_catching_routine =
            Client::KeyCatchingRoutine::KeyCatchingRoutineFactory::createInstance();
        auto interface = Client::Interface::InterfaceFactory::createInstance(settings_manager);
        auto controller = Client::Controller::ControllerFactory::createInstance(
            server_proxy, interface, key_catching_routine, settings_manager);

        key_catching_routine->start();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}