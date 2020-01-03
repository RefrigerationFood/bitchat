#pragma once

#include <ServerProxy/IServerProxy.hpp>

namespace Client {
    namespace ServerProxy {
        namespace ServerProxyFactory {
            ServerProxyPtr createInstance(const std::string& host, const std::string& port);
        }
    }
}