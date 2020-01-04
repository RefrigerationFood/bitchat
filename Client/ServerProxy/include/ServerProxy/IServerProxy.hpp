#pragma once

#include <Common/message.hpp>
#include <functional>
#include <memory>

namespace Client {
namespace ServerProxy {
using ActionCallback = std::function<void(EAction, const message_t&)>;

class IServerProxy
{
public:
    virtual ~IServerProxy() = default;

    virtual void sendMessage(const message_t& msg) = 0;
    virtual void setOnActionCallback(ActionCallback callback) = 0;
};

using ServerProxyPtr = std::shared_ptr<IServerProxy>;
} // namespace ServerProxy
} // namespace Client