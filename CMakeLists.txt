cmake_minimum_required(VERSION 3.10)
project(SimpleMineSweeper LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES "src/*.c")
find_library(CURSES_LIB curses REQUIRED)

add_executable(ms ${SRC_FILES})
target_include_directories(ms PRIVATE include)
target_link_libraries(ms PRIVATE ${CURSES_LIB})
