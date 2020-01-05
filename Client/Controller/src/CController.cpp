#include "CController.hpp"

#include <iostream>

using namespace Client::Controller;

CController::CController(
    ServerProxy::ServerProxyPtr server_proxy,
    Interface::InterfacePtr interface,
    KeyCatchingRoutine::KeyCatchingRoutinePtr key_catching_routine)
    : m_server_proxy(std::move(server_proxy))
    , m_interface(std::move(interface))
    , m_key_catching_routine(std::move(key_catching_routine))
{
    m_interface->setDraft(m_draft);

    m_server_proxy->setOnActionCallback(
        [this](EAction action, const message_t& message) { processInputAction(action, message); });
    m_key_catching_routine->setOnKeyPressedCallback([this](char c) { processInputKey(c); });
}

void CController::processInputKey(char c)
{
    constexpr char c_enter_key{10};
    constexpr char c_backspace_key{127};

    switch (c)
    {
        case c_enter_key:
            m_message.header.action = EAction::Message;
            m_message.header.size = strlen(m_draft.c_str());
            memcpy(m_message.body, m_draft.c_str(), m_message.header.size);
            m_server_proxy->sendMessage(m_message);
            m_draft.clear();
            m_interface->setDraft(m_draft);
            break;
        case c_backspace_key:
            if (!m_draft.empty())
            {
                m_draft.resize(m_draft.size() - 1);
                m_interface->setDraft(m_draft);
            }
            break;
        default:
            m_draft += c;
            m_interface->setDraft(m_draft);
            break;
    }
}

void CController::processInputAction(EAction action, const message_t& message)
{
    switch (action)
    {
        case EAction::Message:
            m_messages.push_back({"unknown", std::string(message.body, message.header.size)});
            m_interface->setMessages(m_messages);
            break;
        default:
            break;
    }
}
