#pragma once

#include <Interface/IInterface.hpp>
#include <mutex>

namespace Client {
namespace Interface {
class CInterface : public IInterface
{
public:
    CInterface();
    ~CInterface();
    void setDraft(const std::string& text) final;
    void setMessages(const std::vector<Client::Common::Types::ChatMessage>& messages) final;

private:
    void render();

private:
    std::string m_draft;
    std::vector<Client::Common::Types::ChatMessage> m_messages;
    int m_length;
    int m_width;
    std::mutex m_mutex;
};
} // namespace Interface
} // namespace Client