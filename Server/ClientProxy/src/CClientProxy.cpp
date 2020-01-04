#include "CServerProxy.hpp"

#include <boost/bind.hpp>

#include <Common/helper_functions.hpp>
#include <iostream>

using namespace Server::ClientProxy;

CClientProxy::CClientProxy(boost::asio::ip::tcp::socket socket)
: m_socket(std::move(socket))
{
    boost::asio::async_read(m_socket,
                            toBuffer(m_tmp_message),
                            boost::bind(&CClientProxy::handleRead, this,
                                boost::asio::placeholders::error));
}

void CClientProxy::sendMessage(const message_t& msg)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_tmp_message = msg;
    m_socket.async_write_some(toBuffer(m_tmp_message),
        boost::bind(&CClientProxy::handleWrite, this,boost::asio::placeholders::error));
}

void CClientProxy::setOnActionCallback(ActionCallback callback)
{
    m_action_callback = callback;
}

void CClientProxy::handleRead(const boost::system::error_code &error)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!error && m_tmp_message.isValid())
    {
        boost::asio::async_read(m_socket,
                                toBuffer(m_tmp_message),
                                boost::bind(&CClientProxy::handleRead, this,
                                            boost::asio::placeholders::error));

        if (m_action_callback)
        {
            std::thread t(m_action_callback, m_tmp_message.header.action, m_tmp_message);
            t.detach();
        }
        else
        {
            std::cerr << "*** ACTION CALLBACK IS NOT SET IN CLIENT PROXY***" << std::endl;
        }
    }
    else
    {
        std::cerr << "*** ERROR WHILE READING DATA FROM SOCKET ***" << std::endl;
    }
}

void CClientProxy::handleWrite(const boost::system::error_code &error)
{
    if (error)
    {
        std::cerr << "*** ERROR WHILE WRITING DATA IN SOCKET ***" << std::endl;
    }
}
