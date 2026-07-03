cmake_minimum_required(VERSION 4.2)
project(geometry_skirmishes)

set(CMAKE_CXX_STANDARD 26)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)


add_executable(geometry_skirmishes main.cpp
        src/core/Game.cpp
        src/core/Game.h
        src/math/Vector.hpp
        src/entities/Entity.hpp
        src/core/EntityManager.cpp
        src/core/EntityManager.hpp
        src/entities/EntityTag.hpp
        src/entities/Component.hpp
        src/random/RandomGenerator.cpp
        src/systems/Renderer.cpp
        src/systems/Renderer.hpp
        src/core/InputState.hpp
        src/systems/InputSystem.cpp
        src/systems/InputSystem.hpp
        src/common/Types.hpp
        src/common/Color.cpp
        src/common/Color.hpp
)

target_include_directories(geometry_skirmishes PRIVATE src)

target_link_libraries(geometry_skirmishes PRIVATE SDL3::SDL3)