#pragma once

#include "message.hpp"

#include <boost/asio.hpp>

namespace {
    boost::asio::mutable_buffers_1 toBuffer(message_t& message)
    {
        return boost::asio::buffer(toCharPtr(message), c_message_size);
    }
}