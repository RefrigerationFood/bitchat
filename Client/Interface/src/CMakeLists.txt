set(INTERFACE_SRC_TARGET interface_src)

add_library(
        ${INTERFACE_SRC_TARGET}
        CInterface.cpp
        InterfaceFactory.cpp)
target_link_libraries(
        ${INTERFACE_SRC_TARGET}
        PUBLIC ${CURSES_LIBRARIES}
        PUBLIC interface_interface
        PUBLIC settings_manager_interface
        PUBLIC common)