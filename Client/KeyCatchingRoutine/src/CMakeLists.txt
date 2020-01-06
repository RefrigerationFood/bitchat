set(KEY_CATCHING_ROUTINE_SRC_TARGET key_catching_routine_src)

find_package(Curses REQUIRED)

add_library(
        ${KEY_CATCHING_ROUTINE_SRC_TARGET}
        CKeyCatchingRoutine.cpp
        KeyCatchingRoutineFactory.cpp)
target_link_libraries(
        ${KEY_CATCHING_ROUTINE_SRC_TARGET}
        PUBLIC key_catching_routine_interface
        PUBLIC ${CURSES_LIBRARIES}
        PUBLIC common)

