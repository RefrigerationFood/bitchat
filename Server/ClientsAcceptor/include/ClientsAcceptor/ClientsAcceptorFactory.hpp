#pragma once

#include <boost/asio.hpp>
#include "IClientsAcceptor.hpp"

namespace Server {
namespace ClientsAcceptor {
namespace ClientsAcceptorFactory {
ClientsAcceptorPtr createInstance(
    boost::asio::io_service& io_service,
    const boost::asio::ip::tcp::endpoint& endpoint);
}
} // namespace ClientsAcceptor
} // namespace Server