#pragma once

#include <Common/action.hpp>
#include <Common/message.hpp>
#include <memory>

namespace Client {
namespace Controller {
class IController
{
public:
    virtual void processInputKey(char c) = 0;
    virtual void processInputAction(EAction action, const message_t& message) = 0;
};

using ControllerPtr = std::shared_ptr<IController>;

} // namespace Controller
} // namespace Client