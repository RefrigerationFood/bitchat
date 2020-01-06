set(CLIENT_TARGET client)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(ServerProxy)
add_subdirectory(KeyCatchingRoutine)
add_subdirectory(Controller)
add_subdirectory(Interface)
add_subdirectory(Common)
add_subdirectory(SettingsManager)

add_executable(${CLIENT_TARGET} client.cpp)
target_link_libraries(
    ${CLIENT_TARGET}
    PUBLIC server_proxy_src
    PUBLIC controller_src
    PUBLIC interface_src
    PUBLIC settings_manager_src
    PUBLIC key_catching_routine_src
    PRIVATE ${USED_LIBS}
    PUBLIC ${CURSES_LIBRARIES}
    PRIVATE common)