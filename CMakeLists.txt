cmake_minimum_required(VERSION 3.16)

project(
    simulation_framework
    VERSION 0.1.0
    LANGUAGES CXX
)

add_executable(
    simulation_framework
    src/main.cpp
    src/fixedComponents.cpp
    src/continuousComponents.cpp
    src/eventComponents.cpp
    src/simulationRuntime.cpp
)

target_include_directories(
    simulation_framework
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(
    simulation_framework
    PRIVATE
        cxx_std_20
)

set_target_properties(
    simulation_framework
    PROPERTIES
        CXX_EXTENSIONS OFF
)

if(MSVC)
    target_compile_options(
        simulation_framework
        PRIVATE
            /W4
            /permissive-
    )
else()
    target_compile_options(
        simulation_framework
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
endif()