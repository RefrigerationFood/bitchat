set(CLIENT_TARGET client)

add_subdirectory(ServerProxy)
add_subdirectory(KeyCatchingRoutine)

add_executable(${CLIENT_TARGET} client.cpp)
target_link_libraries(
    ${CLIENT_TARGET}
    PUBLIC server_proxy_src
    PUBLIC key_catching_routine_src
    PRIVATE ${USED_LIBS}
    PRIVATE common)