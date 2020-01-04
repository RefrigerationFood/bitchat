set(CLIENTS_ACCEPTOR_INTERFACE_TARGET clients_acceptor_interface)

add_library(${CLIENTS_ACCEPTOR_INTERFACE_TARGET} INTERFACE)
target_include_directories(${CLIENTS_ACCEPTOR_INTERFACE_TARGET} INTERFACE include/)

add_subdirectory(src)