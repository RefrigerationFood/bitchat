#pragma once

#include <boost/asio.hpp>
#include "IClientProxy.hpp"

namespace Server {
namespace ClientProxy {
namespace ClientProxyFactory {
ClientProxyPtr createInstance(boost::asio::ip::tcp::socket socket);
}
} // namespace ClientProxy
} // namespace Server