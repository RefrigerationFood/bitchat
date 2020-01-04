#pragma once

#include "message.hpp"

#include <boost/asio.hpp>

namespace {
char* toCharPtr(message_t& message)
{
    return reinterpret_cast<char*>(&message);
}

boost::asio::mutable_buffers_1 toBuffer(message_t& message)
{
    return boost::asio::buffer(toCharPtr(message), c_message_size);
}
} // namespace