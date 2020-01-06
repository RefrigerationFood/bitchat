#include <Controller/ControllerFactory.hpp>
#include "CController.hpp"

namespace Client {
namespace Controller {
namespace ControllerFactory {

ControllerPtr createInstance(
    ServerProxy::ServerProxyPtr server_proxy,
    Interface::InterfacePtr interface,
    KeyCatchingRoutine::KeyCatchingRoutinePtr key_catching_routine,
    SettingsManager::SettingsManagerPtr settings_manager)
{
    return ControllerPtr(new CController(
        std::move(server_proxy),
        std::move(interface),
        std::move(key_catching_routine),
        std::move(settings_manager)));
}

} // namespace ControllerFactory
} // namespace Controller
} // namespace Client