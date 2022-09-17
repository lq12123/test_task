cmake_minimum_required(VERSION 3.14)

project(mylib LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network Concurrent)

file(GLOB CPP_FILES "*.cpp")
file(GLOB HEADER_FILES "*.h**")
add_library(${PROJECT_NAME} SHARED
  ${CPP_FILES}
  ${HEADER_FILES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PATH}
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_directories(${PROJECT_NAME} PRIVATE)
target_link_libraries(${PROJECT_NAME}
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Concurrent
)

target_compile_definitions(${PROJECT_NAME} PRIVATE MYLIB_LIBRARY)
