set(COMMON_TARGET common)

add_library(${COMMON_TARGET} INTERFACE)
target_include_directories(${COMMON_TARGET} INTERFACE include/)