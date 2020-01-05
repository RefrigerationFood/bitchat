#pragma once

#include <memory>

namespace Client {
namespace Controller {
class IController
{
public:
    virtual void processInput(char c) = 0;
};

using ControllerPtr = std::shared_ptr<IController>;

} // namespace Controller
} // namespace Client