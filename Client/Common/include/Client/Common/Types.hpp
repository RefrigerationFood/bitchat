#pragma once

#include <string>

namespace Client {
namespace Common {
namespace Types {

struct ChatMessage
{
    std::string author;
    std::string text;
};

} // namespace Types
} // namespace Common
} // namespace Client