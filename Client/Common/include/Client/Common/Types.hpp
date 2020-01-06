#pragma once

#include <string>

namespace Client {
namespace Common {
namespace Types {

struct ChatMessage
{
    std::string author;
    std::string text;
    bool from_current_user;
};

} // namespace Types
} // namespace Common
} // namespace Client