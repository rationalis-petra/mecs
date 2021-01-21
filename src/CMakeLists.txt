# specify the minimum version required for CMake

cmake_minimum_required(VERSION 3.10)

# Set output output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(ecs)
add_subdirectory(physics)
add_subdirectory(graphics)

add_subdirectory(test_app)


