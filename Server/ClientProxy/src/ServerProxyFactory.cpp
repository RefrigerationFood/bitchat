#include "CServerProxy.hpp"

namespace Server {
    namespace ClientProxy {
        namespace ClientProxyFactory {
            ClientProxyPtr createInstance(boost::asio::ip::tcp::socket socket)
            {
                return ClientProxyPtr(new CClientProxy(std::move(socket)));
            }
        }
    }
}