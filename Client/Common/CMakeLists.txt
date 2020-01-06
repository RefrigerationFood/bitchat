set(COMMON_INTERFACE_TARGET client_common_interface)

add_library(${COMMON_INTERFACE_TARGET} INTERFACE)
target_include_directories(${COMMON_INTERFACE_TARGET} INTERFACE include/)
