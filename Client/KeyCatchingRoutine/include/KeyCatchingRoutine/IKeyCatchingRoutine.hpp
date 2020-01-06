#pragma once

#include <functional>
#include <memory>

namespace Client {
namespace KeyCatchingRoutine {

using KeyPressedCallback = std::function<void(char)>;

class IKeyCatchingRoutine
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void setOnKeyPressedCallback(KeyPressedCallback callback) = 0;
};

using KeyCatchingRoutinePtr = std::shared_ptr<IKeyCatchingRoutine>;

} // namespace KeyCatchingRoutine
} // namespace Client