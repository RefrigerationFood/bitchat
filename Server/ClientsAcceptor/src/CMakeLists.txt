set(CLIENTS_ACCEPTOR_SRC_TARGET clients_acceptor_src)

add_library(
    ${CLIENTS_ACCEPTOR_SRC_TARGET}
    CClientsAcceptor.cpp
    ClientsAcceptorFactory.cpp)
target_link_libraries(
    ${CLIENTS_ACCEPTOR_SRC_TARGET}
    PUBLIC clients_acceptor_interface
    PUBLIC common)

