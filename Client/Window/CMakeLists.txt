set(WINDOW_INTERFACE_TARGET window_interface)

add_library(${WINDOW_INTERFACE_TARGET} INTERFACE)
target_include_directories(${WINDOW_INTERFACE_TARGET} INTERFACE include/)

#add_subdirectory(src)