cmake_minimum_required(VERSION 3.14)

project(cli LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
 set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(cli_VERSION_MAJOR 0)
set(cli_VERSION_MINOR 0)
set(cli_VERSION_PATCH 1)

set(cli_VERSION "${cli_VERSION_MAJOR}.${cli_VERSION_MINOR}.${cli_VERSION_PATCH}")

set(PATH_TO_MYLIB ${CMAKE_SOURCE_DIR}/src/mylib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake/modules
    ${CMAKE_MODULE_PATH}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-sized-deallocation")

configure_file(
    "${PROJECT_SOURCE_DIR}/version.h.in"
    "${PROJECT_BINARY_DIR}/version.h"
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network Concurrent)
find_package(_OpenSSL 1.1 EXACT REQUIRED)

add_executable(cli
  main.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${PATH_TO_MYLIB}
    PRIVATE include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    ssl
    crypto
    mylib
)

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_BINDIR})
