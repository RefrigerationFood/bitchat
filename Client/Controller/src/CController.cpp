#include "CController.hpp"

#include <iostream>
#include <random>

using namespace Client::Controller;

CController::CController(
    ServerProxy::ServerProxyPtr server_proxy,
    Interface::InterfacePtr interface,
    KeyCatchingRoutine::KeyCatchingRoutinePtr key_catching_routine,
    SettingsManager::SettingsManagerPtr settings_manager)
    : m_server_proxy(std::move(server_proxy))
    , m_interface(std::move(interface))
    , m_key_catching_routine(std::move(key_catching_routine))
    , m_settings_manager(std::move(settings_manager))
    , m_uuid(generateUUID())
    , m_name_subscription(m_settings_manager->getClientNameAttribute(), m_name, m_mutex)
{
    m_interface->setDraft(m_draft);

    m_server_proxy->setOnActionCallback(
        [this](EAction action, const message_t& message) { processInputAction(action, message); });
    m_key_catching_routine->setOnKeyPressedCallback([this](char c) { processInputKey(c); });
}

void CController::processInputKey(char c)
{
    constexpr char c_enter_key{10};
    constexpr char c_backspace_key{7};

    switch (c)
    {
        case c_enter_key:
            if (!m_draft.empty())
            {
                m_message = generateMessage(m_draft);
                m_server_proxy->sendMessage(m_message);
                m_draft.clear();
                m_interface->setDraft(m_draft);
            }
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
            const auto* chat_message = reinterpret_cast<const chat_message_t*>(message.body);

            m_messages.push_back({std::string(chat_message->author, chat_message->author_size),
                                  std::string(chat_message->text, chat_message->text_size),
                                  message.header.author_id == m_uuid});
            m_interface->setMessages(m_messages);
            break;
            // default:
            //    break;
    }
}

uint64_t CController::generateUUID()
{
    std::mt19937_64 engine(std::random_device{}());
    std::uniform_int_distribution<uint64_t> distribution;

    return distribution(engine);
}

message_t CController::generateMessage(const std::string& text)
{
    message_t msg;
    chat_message_t chat_message;

    {
        std::lock_guard<std::mutex> lock(m_mutex);
        strcpy(chat_message.author, m_name.c_str());
    }
    strcpy(chat_message.text, text.c_str());
    chat_message.author_size = strlen(chat_message.author);
    chat_message.text_size = strlen(chat_message.text);

    msg.header.author_id = m_uuid;
    msg.header.action = EAction::Message;
    msg.header.validation_code = c_valid_code;
    msg.header.size = sizeof(chat_message);
    memcpy(msg.body, &chat_message, msg.header.size);

    return msg;
}
