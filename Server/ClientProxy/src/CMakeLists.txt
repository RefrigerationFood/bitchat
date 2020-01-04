set(CLIENT_PROXY_SRC_TARGET client_proxy_src)

add_library(
    ${CLIENT_PROXY_SRC_TARGET}
    CClientProxy.cpp
        ServerProxyFactory.cpp)
target_link_libraries(
    ${CLIENT_PROXY_SRC_TARGET}
    PUBLIC client_proxy_interface
    PUBLIC common)

