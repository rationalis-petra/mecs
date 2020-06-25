# specify the minimum version required for CMake

cmake_minimum_required(VERSION 3.10)

# Set output output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(engine)

include_directories(
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/include/engine/
    ${PROJECT_SOURCE_DIR}/libs/include/)


add_library(game components/camera.c
                 components/rigidbody.c
                 components/creature.c
                 components/info.c
                 components/transform.c
                 systems/enemy_system.c
                 systems/input_system.c
                 systems/render_system.c
                 systems/physics_system.c
                 systems/utils.c
                 templates/enemy_template.c
                 templates/player_template.c)
