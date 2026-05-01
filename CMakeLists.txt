cmake_minimum_required(VERSION 3.16)

project(Viktorina VERSION 0.1 LANGUAGES CXX)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/generators")

set(CMAKE_PREFIX_PATH "/usr/lib/cmake/Qt6")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(nlohmann_json_DIR "${CMAKE_BINARY_DIR}")

find_package(nlohmann_json REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(
    PROJECT_SOURCES
    main.cpp
    mainWindow.cpp
    mainWindow.h
    questionaire.ui
)

add_executable(Viktorina ${PROJECT_SOURCES})

target_link_libraries(
    Viktorina PRIVATE
    nlohmann_json::nlohmann_json
    Qt6::Widgets
)
