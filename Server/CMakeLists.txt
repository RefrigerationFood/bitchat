set(SERVER_TARGET server)

add_executable(${SERVER_TARGET} server.cpp)
target_link_libraries(
    ${SERVER_TARGET}
    PUBLIC client_proxy_src
    PUBLIC clients_acceptor_src
    PRIVATE ${USED_LIBS}
    PRIVATE common)

add_subdirectory(ClientProxy)
add_subdirectory(ClientsAcceptor)