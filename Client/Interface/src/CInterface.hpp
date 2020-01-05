#pragma once

#include <Interface/IInterface.hpp>

namespace Client {
namespace Interface {
class CInterface : public IInterface
{
public:
    CInterface();
    ~CInterface();
    void setDraft(const std::string& text) final;
    void setMessages(const std::vector<Client::Common::Types::ChatMessage>& text) final;

private:
    void render();

private:
    std::string m_draft;
    int m_length;
    int m_width;
};
} // namespace Interface
} // namespace Client