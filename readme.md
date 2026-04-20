# Vulkan Renderer

A 3D renderer built from scratch in C++ using Vulkan.

## what it does

- Renders 3D meshes with a depth buffer and perspective projection
- Orbit camera with mouse drag and scroll to zoom
- Runtime mesh switching — swap between shapes without restarting
- ImGui control panel in the viewport
- Built-in mesh primitives: cube, sphere, pyramid

## dependencies

- [Vulkan SDK](https://vulkan.lunarg.com/)
- [GLFW](https://www.glfw.org/)
- [GLM](https://github.com/g-truc/glm)
- [ImGui v1.89.9](https://github.com/ocornut/imgui) (git submodule)

## building

```bash
git clone --recurse-submodules https://github.com/ayushsucksaf/vk-renderer.git
cd vk-renderer
mkdir build && cd build
cmake ..
make
```

Shaders are to be compiled as `.spv` files in `cmake-build-debug/shaders/`. If you modify the GLSL source, recompile with `glslc`.

## platform

Built and tested on Arch Linux with Wayland (Hyprland). Should work on any Linux system with Vulkan support.

