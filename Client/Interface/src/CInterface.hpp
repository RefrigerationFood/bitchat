#pragma once

#include <Client/Common/Attribute/RAIISubscription.hpp>
#include <Interface/IInterface.hpp>
#include <SettingsManager/ISettingsManager.hpp>
#include <mutex>

namespace Client {
namespace Interface {
using Client::Common::RAIISubscription;

class CInterface : public IInterface
{
public:
    explicit CInterface(SettingsManager::SettingsManagerPtr settings_manager);
    ~CInterface();
    void setDraft(const std::string& text) final;
    void setMessages(const std::vector<Client::Common::Types::ChatMessage>& messages) final;

private:
    void render();

private:
    SettingsManager::SettingsManagerPtr m_settings_manager;
    RAIISubscription<int> m_length_subscription;
    RAIISubscription<int> m_width_subscription;
    std::string m_draft;
    std::vector<Client::Common::Types::ChatMessage> m_messages;
    int m_length;
    int m_width;
    std::mutex m_mutex;
};
} // namespace Interface
} // namespace Client