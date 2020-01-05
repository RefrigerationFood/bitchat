#include <Controller/ControllerFactory.hpp>
#include "CController.hpp"

namespace Client {
namespace Controller {
namespace ControllerFactory {
ControllerPtr createInstance(
    ServerProxy::ServerProxyPtr server_proxy,
    Interface::InterfacePtr interface,
    KeyCatchingRoutine::KeyCatchingRoutinePtr key_catching_routine)
{
    return ControllerPtr(new CController(
        std::move(server_proxy), std::move(interface), std::move(key_catching_routine)));
}
} // namespace ControllerFactory
} // namespace Controller
} // namespace Client