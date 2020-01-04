#include "CClientsAcceptor.hpp"

#include <iostream>
#include <boost/bind.hpp>

using namespace Server::ClientsAcceptor;

CClientsAcceptor::CClientsAcceptor(boost::asio::io_service &io_service, const boost::asio::ip::tcp::endpoint& endpoint)
: m_io_service(io_service)
, m_endpoint(endpoint)
, m_pending_socket(m_io_service)
, m_acceptor(m_io_service, endpoint)
{
    m_acceptor.async_accept(m_pending_socket,
                            boost::bind(&CClientsAcceptor::handleConnect, this, boost::asio::placeholders::error));
}

void CClientsAcceptor::setOnClientConnected(ClientConnectedCallback callback)
{
    m_client_connected_callback = callback;
}

void CClientsAcceptor::handleConnect(const boost::system::error_code &error)
{
    if (!error)
    {
        if (m_client_connected_callback)
        {
            m_client_connected_callback(std::move(m_pending_socket));
            m_pending_socket = tcp::socket(m_io_service);
            m_acceptor.async_accept(m_pending_socket,
                                    boost::bind(&CClientsAcceptor::handleConnect, this, boost::asio::placeholders::error));
        }
        else
        {
            std::cerr << "*** ON CLIENT CONNECTED CALLBACK IS NOT SET ***" << std::endl;
        }
    }
    else
    {
        std::cerr << "*** ERROR WHILE CONNECTING CLIENT ***" << std::endl;
    }
}
