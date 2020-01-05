set(INTERFACE_INTERFACE_TARGET interface_interface)

add_library(${INTERFACE_INTERFACE_TARGET} INTERFACE)
target_include_directories(${INTERFACE_INTERFACE_TARGET} INTERFACE include/)
target_link_libraries(
        ${INTERFACE_INTERFACE_TARGET}
        INTERFACE client_common_interface)

#add_subdirectory(src)