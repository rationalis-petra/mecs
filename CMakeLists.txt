# specify the minimum version required for CMake

cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
# Projectn's Name

project(enigma)

# Set output output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included

include_directories(
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/include/engine/
    ${PROJECT_SOURCE_DIR}/libs/include/)

add_subdirectory(src)
add_subdirectory(libs)

add_executable(enigma src/main.c)

target_link_libraries(enigma game engine glad)
target_link_libraries(enigma glfw GL X11 pthread Xrandr Xi dl m)
