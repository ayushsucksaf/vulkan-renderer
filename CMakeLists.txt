cmake_minimum_required(VERSION 4.3)
project(render)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(render src/main.cpp
        src/Vulkanengine.h
        src/Vulkanengine.cpp
        src/Mesh.h
        src/Mesh.cpp
        src/Vertex.h
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_vulkan.cpp)

target_include_directories(render PRIVATE imgui imgui/backends)
target_link_libraries(render Vulkan::Vulkan glfw glm::glm)