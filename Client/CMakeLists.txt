set(CLIENT_TARGET client)

add_subdirectory(ServerProxy)
add_subdirectory(KeyCatchingRoutine)
add_subdirectory(Controller)
add_subdirectory(Interface)
add_subdirectory(Common)

add_executable(${CLIENT_TARGET} client.cpp)
target_link_libraries(
    ${CLIENT_TARGET}
    PUBLIC server_proxy_src
    PUBLIC controller_src
    PUBLIC interface_src
    PUBLIC key_catching_routine_src
    PRIVATE ${USED_LIBS}
    PRIVATE common)