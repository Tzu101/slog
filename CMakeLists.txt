cmake_minimum_required(VERSION 3.10.0)

set(PROJECT_NAME log)

project(${PROJECT_NAME})
add_library(${PROJECT_NAME} src/log.cpp)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_executable(playground playground/main.cpp)
    target_link_libraries(playground PRIVATE ${PROJECT_NAME})
endif()

