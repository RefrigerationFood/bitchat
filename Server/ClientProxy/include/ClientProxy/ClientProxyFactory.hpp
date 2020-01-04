#pragma once

#include <ClientProxy/IClientProxy.hpp>
#include <boost/asio.hpp>

namespace Server {
    namespace ClientProxy {
        namespace ClientProxyFactory {
            ClientProxyPtr createInstance(boost::asio::ip::tcp::socket socket);
        }
    }
}