cmake_minimum_required(VERSION 3.10.0)

cmake_policy(SET CMP0076 NEW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME slog)

# Project
project(${PROJECT_NAME})
add_library(${PROJECT_NAME} INTERFACE)

# Files
target_include_directories(${PROJECT_NAME} INTERFACE src)
target_sources(${PROJECT_NAME} INTERFACE
    src/slog.h
)

find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE spdlog::spdlog_header_only)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_executable(playground playground/main.cpp)
    target_link_libraries(playground PRIVATE ${PROJECT_NAME})
endif()
