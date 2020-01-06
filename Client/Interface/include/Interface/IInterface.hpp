#pragma once

#include <Client/Common/Types.hpp>
#include <memory>
#include <string>
#include <vector>

namespace Client {
namespace Interface {
class IInterface
{
public:
    virtual void setDraft(const std::string& text) = 0;
    virtual void setMessages(const std::vector<Client::Common::Types::ChatMessage>& messages) = 0;
};

using InterfacePtr = std::shared_ptr<IInterface>;
} // namespace Interface
} // namespace Client