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
    Qt${QT_VERSION_MAJOR}::Concurrent
    ssl
    crypto
    mylib
)

file(GLOB EXCLUDE_QTLIB
    "${PATH_TO_QT}/lib/*Qt${QT_VERSION_MAJOR}Network*"
    "${PATH_TO_QT}/lib/*Qt${QT_VERSION_MAJOR}DBus*"
)

file(GLOB DEPS
    "${PATH_TO_QT}/lib/*.so*")
foreach(lib ${DEPS})
    if (NOT ${lib} IN_LIST EXCLUDE_QTLIB)
        list(APPEND LINKED_QTLIBS ${lib})
    endif()
endforeach()

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${LINKED_QTLIBS}
    TYPE LIB)
install(IMPORTED_RUNTIME_ARTIFACTS
    mylib)
