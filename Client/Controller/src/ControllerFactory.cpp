#include <Controller/ControllerFactory.hpp>
#include "CController.hpp"

namespace Client {
namespace Controller {
namespace ControllerFactory {
ControllerPtr createInstance(
    ServerProxy::ServerProxyPtr server_proxy,
    Interface::InterfacePtr interface)
{
    return ControllerPtr(new CController(std::move(server_proxy), std::move(interface)));
}
} // namespace ControllerFactory
} // namespace Controller
} // namespace Client