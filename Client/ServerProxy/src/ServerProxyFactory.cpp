#include "CServerProxy.hpp"

namespace Client {
namespace ServerProxy {
namespace ServerProxyFactory {
ServerProxyPtr createInstance(const std::string& host, const std::string& port)
{
    return ServerProxyPtr(new CServerProxy(host, port));
}
} // namespace ServerProxyFactory
} // namespace ServerProxy
} // namespace Client