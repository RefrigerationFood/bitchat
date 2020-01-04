set(SERVER_PROXY_SRC_TARGET server_proxy_src)

add_library(
    ${SERVER_PROXY_SRC_TARGET}
    CServerProxy.cpp
    ServerProxyFactory.cpp)
target_link_libraries(
    ${SERVER_PROXY_SRC_TARGET}
    PUBLIC server_proxy_interface
    PUBLIC common)

