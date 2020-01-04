#pragma once

#include <Common/message.hpp>
#include <functional>
#include <memory>

namespace Server {
    namespace ClientProxy {
        using ActionCallback = std::function<void(EAction, const message_t&)>;

        class IClientProxy
        {
        public:
            virtual ~IClientProxy() = default;

            virtual void sendMessage(const message_t& msg) = 0;
            virtual void setOnActionCallback(ActionCallback callback) = 0;
        };

        using ClientProxyPtr = std::shared_ptr<IClientProxy>;
    }
}