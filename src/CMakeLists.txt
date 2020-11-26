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


add_library(game components/camera.cpp
                 components/rigidbody.cpp
                 components/model.cpp
                 components/info.cpp
                 components/attachment.cpp
                 components/sensor.cpp
                 components/actuator.cpp
                 components/agent.cpp

                 systems/enemy_system.cpp
                 systems/input_system.cpp
                 systems/render_system.cpp
                 #systems/ai_system.cpp
                 systems/physics_system.cpp
                 systems/physics/sat_test.cpp
                 systems/utils.cpp

                 constructors/enemy.cpp
                 constructors/player.cpp
                 constructors/floor.cpp)
