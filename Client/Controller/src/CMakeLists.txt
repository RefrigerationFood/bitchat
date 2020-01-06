set(CONTROLLER_SRC_TARGET controller_src)

add_library(
        ${CONTROLLER_SRC_TARGET}
        CController.cpp
        ControllerFactory.cpp)
target_link_libraries(
        ${CONTROLLER_SRC_TARGET}
        PUBLIC controller_interface
        PUBLIC server_proxy_interface
        PUBLIC client_common_interface
        PUBLIC interface_interface
        PUBLIC key_catching_routine_interface
        PUBLIC settings_manager_interface
        PUBLIC common)