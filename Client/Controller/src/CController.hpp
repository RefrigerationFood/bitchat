#pragma once

#include <Controller/IController.hpp>
#include <Interface/IInterface.hpp>
#include <KeyCatchingRoutine/IKeyCatchingRoutine.hpp>
#include <ServerProxy/IServerProxy.hpp>

namespace Client {
namespace Controller {
class CController : public IController
{
public:
    CController(
        ServerProxy::ServerProxyPtr server_proxy,
        Interface::InterfacePtr interface,
        KeyCatchingRoutine::KeyCatchingRoutinePtr key_catching_routine);
    void processInputKey(char c) final;
    void processInputAction(EAction action, const message_t& message) final;

private:
    ServerProxy::ServerProxyPtr m_server_proxy;
    Interface::InterfacePtr m_interface;
    KeyCatchingRoutine::KeyCatchingRoutinePtr m_key_catching_routine;
    std::vector<Client::Common::Types::ChatMessage> m_messages;
    message_t m_message;
    std::string m_draft;
};

} // namespace Controller
} // namespace Client