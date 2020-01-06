#pragma once

#include "IController.hpp"

#include <Interface/IInterface.hpp>
#include <KeyCatchingRoutine/IKeyCatchingRoutine.hpp>
#include <ServerProxy/IServerProxy.hpp>
#include <SettingsManager/ISettingsManager.hpp>

namespace Client {
namespace Controller {
namespace ControllerFactory {
ControllerPtr createInstance(
    ServerProxy::ServerProxyPtr server_proxy,
    Interface::InterfacePtr interface,
    KeyCatchingRoutine::KeyCatchingRoutinePtr key_catching_routine,
    SettingsManager::SettingsManagerPtr settings_manager);
}
} // namespace Controller
} // namespace Client