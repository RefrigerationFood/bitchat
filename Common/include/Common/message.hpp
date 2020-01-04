#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "action.hpp"

constexpr size_t c_valid_code{0x0123456789ABCDEF};
constexpr size_t c_max_body_size{1U << 10};

struct header_t
{
    EAction action;
    size_t size;
    size_t validation_code = c_valid_code;
};

struct message_t
{
    header_t header;
    char body[c_max_body_size];

    bool isValid() { return (header.validation_code == c_valid_code); }
};

constexpr size_t c_header_size{sizeof(header_t)};
constexpr size_t c_message_size{sizeof(message_t)};