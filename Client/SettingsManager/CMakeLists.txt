set(SETTINGS_MANAGER_INTERFACE_TARGET settings_manager_interface)

add_library(${SETTINGS_MANAGER_INTERFACE_TARGET} INTERFACE)
target_include_directories(${SETTINGS_MANAGER_INTERFACE_TARGET} INTERFACE include/)

add_subdirectory(src)