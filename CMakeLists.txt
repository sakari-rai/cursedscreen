cmake_minimum_required(VERSION 3.15)

project(cursedscreen VERSION 1.0)
 
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
    set(CMAKE_PREFIX_PATH ../../LIBS/PDCurses)
    find_path(PDCURSES_INCLUDES curses.h)
    find_library(PDCURSES_LIB NAMES pdcurses REQUIRED HINTS ${PDCURSES_INCLUDES}/wincon)
endif()

add_executable(cursedscreen main.cpp AppState.cpp FrameBuffer.cpp utils/vec2.cpp)

if(MSVC)
    target_include_directories(cursedscreen PRIVATE ${PDCURSES_INCLUDES})
    target_link_libraries(cursedscreen PRIVATE ${PDCURSES_LIB})
else()
    target_link_libraries(cursedscreen PRIVATE ncurses)
endif()



