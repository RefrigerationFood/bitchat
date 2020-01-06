#include "CServerProxy.hpp"

#include <boost/bind.hpp>

#include <Common/helper_functions.hpp>
#include <iostream>

using namespace Client::ServerProxy;

CServerProxy::CServerProxy(const std::string& host, const std::string& port)
    : m_action_callback(nullptr)
    , m_resolver(m_io_service)
    , m_query(host, port)
    , m_endpoint_iterator(m_resolver.resolve(m_query))
    , m_socket(m_io_service)
{
    tcp::endpoint endpoint = *m_endpoint_iterator;
    m_socket.async_connect(
        endpoint,
        boost::bind(&CServerProxy::handleConnect, this, boost::asio::placeholders::error));

    m_io_service_run_thread = std::thread([this]() { m_io_service.run(); });
}

CServerProxy::~CServerProxy()
{
    m_io_service.post([this]() { m_socket.close(); });
    m_io_service_run_thread.join();
}

void CServerProxy::sendMessage(const message_t& msg)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_tmp_message = msg;
    m_socket.async_write_some(
        toBuffer(m_tmp_message),
        boost::bind(&CServerProxy::handleWrite, this, boost::asio::placeholders::error));
}

void CServerProxy::setOnActionCallback(Client::ServerProxy::ActionCallback callback)
{
    m_action_callback = callback;
}

void CServerProxy::handleConnect(const boost::system::error_code& error)
{
    if (!error)
    {
        boost::asio::async_read(
            m_socket,
            toBuffer(m_tmp_message),
            boost::bind(&CServerProxy::handleRead, this, boost::asio::placeholders::error));
    }
    else if (m_endpoint_iterator != tcp::resolver::iterator())
    {
        m_socket.close();
        ++m_endpoint_iterator;
        tcp::endpoint endpoint = *m_endpoint_iterator;
        m_socket.async_connect(
            endpoint,
            boost::bind(&CServerProxy::handleConnect, this, boost::asio::placeholders::error));
    }
    else
    {
        std::cerr << "*** ERROR WHILE CONNECTING TO THE SERVER ***" << std::endl;
    }
}

void CServerProxy::handleRead(const boost::system::error_code& error)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!error && m_tmp_message.isValid())
    {
        boost::asio::async_read(
            m_socket,
            toBuffer(m_tmp_message),
            boost::bind(&CServerProxy::handleRead, this, boost::asio::placeholders::error));

        if (m_action_callback)
        {
            m_action_callback(m_tmp_message.header.action, m_tmp_message);
        }
        else
        {
            std::cerr << "*** ACTION CALLBACK IS NOT SET IN SERVER PROXY***" << std::endl;
        }
    }
    else
    {
        std::cerr << "*** ERROR WHILE READING DATA FROM SOCKET ***" << std::endl;
    }
}

void CServerProxy::handleWrite(const boost::system::error_code& error)
{
    if (error)
    {
        std::cerr << "*** ERROR WHILE WRITING DATA IN SOCKET ***" << std::endl;
    }
}
