set(CLIENT_PROXY_INTERFACE_TARGET client_proxy_interface)

add_library(${CLIENT_PROXY_INTERFACE_TARGET} INTERFACE)
target_include_directories(${CLIENT_PROXY_INTERFACE_TARGET} INTERFACE include/)

add_subdirectory(src)