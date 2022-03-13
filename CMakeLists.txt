cmake_minimum_required(VERSION 3.16)
project(task_dispatcher LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE CMAKE_SOURCE_DIR)

include_directories(${PROJECT_SOURCE_DIR})

set(SOURCE_FILES main.cpp)
add_executable( task-dispatcher ${SOURCE_FILES})

target_include_directories(task-dispatcher PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
