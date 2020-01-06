#pragma once

#include <memory>

namespace Client {
namespace Window {
class IWindow
{
public:
    virtual void resize(uint16_t x, uint16_t y) = 0;
};

using WindowPtr = std::shared_ptr<IWindow>;

} // namespace Window
} // namespace Client