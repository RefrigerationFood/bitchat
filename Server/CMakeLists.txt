set(SERVER_TARGET server)

add_executable(${SERVER_TARGET} server.cpp)
target_link_libraries(
    ${SERVER_TARGET}
    PUBLIC client_proxy_src
    PRIVATE ${USED_LIBS}
    PRIVATE common)

add_subdirectory(ClientProxy)