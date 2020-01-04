#include "CClientsAcceptor.hpp"

namespace Server {
namespace ClientsAcceptor {
namespace ClientsAcceptorFactory {
ClientsAcceptorPtr createInstance(
    boost::asio::io_service& io_service,
    const boost::asio::ip::tcp::endpoint& endpoint)
{
    return ClientsAcceptorPtr(new CClientsAcceptor(io_service, endpoint));
}
} // namespace ClientsAcceptorFactory
} // namespace ClientsAcceptor
} // namespace Server