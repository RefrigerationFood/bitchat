#pragma once

#include <Client/Common/Attribute/RAIISubscription.hpp>
#include <Controller/IController.hpp>
#include <Interface/IInterface.hpp>
#include <KeyCatchingRoutine/IKeyCatchingRoutine.hpp>
#include <ServerProxy/IServerProxy.hpp>
#include <SettingsManager/ISettingsManager.hpp>

#include <mutex>

using Client::Common::RAIISubscription;

namespace Client {
namespace Controller {
class CController : public IController
{
public:
    CController(
        ServerProxy::ServerProxyPtr server_proxy,
        Interface::InterfacePtr interface,
        KeyCatchingRoutine::KeyCatchingRoutinePtr key_catching_routine,
        SettingsManager::SettingsManagerPtr settings_manager);
    void processInputKey(char c) final;
    void processInputAction(EAction action, const message_t& message) final;

private:
    uint64_t generateUUID();
    message_t generateMessage(const std::string& text);

private:
    ServerProxy::ServerProxyPtr m_server_proxy;
    Interface::InterfacePtr m_interface;
    KeyCatchingRoutine::KeyCatchingRoutinePtr m_key_catching_routine;
    SettingsManager::SettingsManagerPtr m_settings_manager;
    std::vector<Client::Common::Types::ChatMessage> m_messages;
    message_t m_message;
    std::string m_draft;
    uint64_t m_uuid;
    std::mutex m_mutex;
    std::string m_name;
    RAIISubscription<std::string> m_name_subscription;
};

} // namespace Controller
} // namespace Client