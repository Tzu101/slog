cmake_minimum_required(VERSION 3.25.0)

cmake_policy(SET CMP0076 NEW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME slog)
set(PROJECT_TYPES_NAME slog_types)

# Project
project(${PROJECT_NAME})

# Types-only library
add_library(${PROJECT_TYPES_NAME} INTERFACE)
target_include_directories(${PROJECT_TYPES_NAME} INTERFACE src)
target_sources(${PROJECT_TYPES_NAME} INTERFACE
    src/slog_types.h
)

# Full functionality library + spdlog
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE src)
target_sources(${PROJECT_NAME} INTERFACE
    src/slog.h
)

find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE spdlog::spdlog_header_only)

if(PROJECT_IS_TOP_LEVEL)
    add_executable(playground playground/main.cpp)
    target_link_libraries(playground PRIVATE ${PROJECT_TYPES_NAME})
endif()
