set(CONTROLLER_INTERFACE_TARGET controller_interface)

add_library(${CONTROLLER_INTERFACE_TARGET} INTERFACE)
target_include_directories(${CONTROLLER_INTERFACE_TARGET} INTERFACE include/)

add_subdirectory(src)