cmake_minimum_required(VERSION 3.14)

project(main LANGUAGES CXX)

set(PATH_TO_QT "${CMAKE_SOURCE_DIR}/Qt5")
set(CMAKE_PREFIX_PATH ${PATH_TO_QT}
    ${CMAKE_PREFIX_PATH}
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-sized-deallocation")
set(OUTPUT_PATH_MYLIB ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_INSTALL_RPATH "/usr/local/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

add_subdirectory(src/mylib)
add_subdirectory(src/cli)
