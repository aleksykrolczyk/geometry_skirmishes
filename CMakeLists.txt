cmake_minimum_required(VERSION 4.2)
project(geometry_skirmishes)

set(CMAKE_CXX_STANDARD 26)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

add_library(imgui
        vendored/imgui/imgui.cpp
        vendored/imgui/imgui_draw.cpp
        vendored/imgui/imgui_tables.cpp
        vendored/imgui/imgui_widgets.cpp

        vendored/imgui/backends/imgui_impl_sdl3.cpp
        vendored/imgui/backends/imgui_impl_sdlrenderer3.cpp
)

target_include_directories(imgui PUBLIC
        vendored/imgui
        vendored/imgui/backends
)

target_link_libraries(imgui PUBLIC SDL3::SDL3)

add_executable(geometry_skirmishes main.cpp
        src/core/Game.cpp
        src/core/Game.h
        src/math/Vector.hpp
        src/entities/Entity.hpp
        src/core/EntityManager.cpp
        src/core/EntityManager.hpp
        src/entities/EntityTag.hpp
        src/entities/Component.hpp
        src/common/Random.hpp
        src/core/Renderer.cpp
        src/core/Renderer.hpp
        src/core/InputState.hpp
        src/common/Types.hpp
        src/common/Color.cpp
        src/common/Color.hpp
        src/core/Physics.hpp
        src/core/DebugUI.cpp
        src/core/DebugUI.hpp
)

target_include_directories(geometry_skirmishes PRIVATE src)

target_link_libraries(geometry_skirmishes PRIVATE
        SDL3::SDL3
        imgui
)