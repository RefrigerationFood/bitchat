#pragma once

#include <boost/asio.hpp>

#include <mutex>
#include <thread>

#include <ClientProxy/IClientProxy.hpp>
#include <Common/message.hpp>

namespace Server {
namespace ClientProxy {
using boost::asio::ip::tcp;

class CClientProxy : public IClientProxy
{
public: // methods
    CClientProxy(boost::asio::ip::tcp::socket socket);
    void sendMessage(const message_t& msg) final;
    void setOnActionCallback(ActionCallback callback) final;

private: // methods
    void handleRead(const boost::system::error_code& error);
    void handleWrite(const boost::system::error_code& error);

private: // fields
    ActionCallback m_action_callback;
    tcp::socket m_socket;
    message_t m_tmp_message;
    std::mutex m_mutex;
};
} // namespace ClientProxy
} // namespace Server