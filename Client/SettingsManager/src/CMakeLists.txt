set(SETTINGS_MANAGER_SRC_TARGET settings_manager_src)

add_library(
        ${SETTINGS_MANAGER_SRC_TARGET}
        CSettingsManager.cpp
        SettingsManagerFactory.cpp)
target_link_libraries(
        ${SETTINGS_MANAGER_SRC_TARGET}
        PUBLIC ${CURSES_LIBRARIES}
        PUBLIC settings_manager_interface
        PUBLIC client_common_interface)

