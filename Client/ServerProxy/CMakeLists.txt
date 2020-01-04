set(SERVER_PROXY_INTERFACE_TARGET server_proxy_interface)

add_library(${SERVER_PROXY_INTERFACE_TARGET} INTERFACE)
target_include_directories(${SERVER_PROXY_INTERFACE_TARGET} INTERFACE include/)

add_subdirectory(src)