# specify the minimum version required for CMake

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_FLAGS "-g -Wall")
# Project name

project(mecs)

# Set output output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included

include_directories(
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/libs/include/)

add_subdirectory(src)
add_subdirectory(libs)

add_executable(mecs src/test_app/main.cpp)

add_library(engine $<TARGET_OBJECTS:ecs>
                   $<TARGET_OBJECTS:physics>
                   $<TARGET_OBJECTS:graphics>)
target_link_libraries(engine glad)

target_link_libraries(mecs sim engine)
target_link_libraries(mecs glfw GL X11 Xrandr Xi dl m)
