cmake_minimum_required(VERSION 3.14)

project(main LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(src/mylib)
add_subdirectory(src/cli)
