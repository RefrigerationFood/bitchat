#pragma once

#include <Interface/IInterface.hpp>
#include <ServerProxy/IServerProxy.hpp>
#include "IController.hpp"

namespace Client {
namespace Controller {
namespace ControllerFactory {
ControllerPtr createInstance(
    ServerProxy::ServerProxyPtr server_proxy,
    Interface::InterfacePtr interface);
}
} // namespace Controller
} // namespace Client