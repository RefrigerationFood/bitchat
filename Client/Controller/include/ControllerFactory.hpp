#pragma once

#include <Interface/IInterface.hpp>
#include <ServerProxy/IServerProxy.hpp>
#include "IController.hpp"

namespace Client {
namespace Controller {
namespace ControllerFactory {
ControllerPtr createInstance(
    const ServerProxy::ServerProxyPtr& server_proxy,
    const Interface::InterfacePtr& interface);
}
} // namespace Controller
} // namespace Client