set(CLIENT_TARGET client)

add_executable(${CLIENT_TARGET} chat_client.cpp)
target_link_libraries(
    ${CLIENT_TARGET}
    PRIVATE ${USED_LIBS}
    PRIVATE common)