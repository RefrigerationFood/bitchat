#pragma once

#include "IClientsAcceptor.hpp"
#include <boost/asio.hpp>

namespace Server {
    namespace ClientsAcceptor {
        namespace ClientsAcceptorFactory {
            ClientsAcceptorPtr createInstance(boost::asio::io_service& io_service,
                                              const boost::asio::ip::tcp::endpoint& endpoint);
        }
    }
}