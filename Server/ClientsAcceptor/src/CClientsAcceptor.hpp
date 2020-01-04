#pragma once

#include <boost/asio.hpp>

#include <mutex>

#include <ClientsAcceptor/IClientsAcceptor.hpp>

namespace Server {
    namespace ClientsAcceptor {
        using boost::asio::ip::tcp;

        class CClientsAcceptor : public IClientsAcceptor
    {
        public:// methods
            CClientsAcceptor(boost::asio::io_service& io_service,
                             const boost::asio::ip::tcp::endpoint& endpoint);
            void setOnClientConnected(ClientConnectedCallback callback) final;

        private:// methods
            void handleConnect(const boost::system::error_code& error);

        private:// fields
            ClientConnectedCallback m_client_connected_callback;
            boost::asio::io_service& m_io_service;
            boost::asio::ip::tcp::endpoint m_endpoint;
            boost::asio::ip::tcp::socket m_pending_socket;
            tcp::acceptor m_acceptor;
            std::mutex m_mutex;
        };
    }
}