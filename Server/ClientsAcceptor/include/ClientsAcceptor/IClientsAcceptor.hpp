#pragma once

#include <boost/asio.hpp>
#include <functional>
#include <memory>

namespace Server {
    namespace ClientsAcceptor {
        using ClientConnectedCallback = std::function<void(boost::asio::ip::tcp::socket m_socket)>;

        class IClientsAcceptor
        {
        public:
            virtual ~IClientsAcceptor() = default;

            virtual void setOnClientConnected(ClientConnectedCallback callback) = 0;
        };

        using ClientsAcceptorPtr = std::shared_ptr<IClientsAcceptor>;
    }
}