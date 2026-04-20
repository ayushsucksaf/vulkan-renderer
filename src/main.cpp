#include <iostream>
#include "Vulkanengine.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;


VulkanEngine* enginePtr = nullptr;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (enginePtr) enginePtr->onMouseButton(button, action);
}

void cursorPosCallback(GLFWwindow* window, double x, double y) {
    if (enginePtr) enginePtr->onMouseMove(x, y);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    if (enginePtr) enginePtr->onScroll(yOffset);
}


int main() {
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);

    if (!glfwInit()) {
        std::cerr << "glfw failed\n";
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "render", nullptr, nullptr);
    if (!window) {
        std::cerr << "window creation failed\n";
        glfwTerminate();
        return -1;
    }

    VulkanEngine engine;
    enginePtr = &engine;

    // register callbacks
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);

    //chose your shape
    engine.setMesh(Mesh::cube());                          // white
    // engine.setMesh(Mesh::cube({1.0f, 0.5f, 0.0f}));       // orange
    // engine.setMesh(Mesh::sphere(20, 20, {0.2f, 0.8f, 1.0f})); // light blue
    // engine.setMesh(Mesh::pyramid());                        // white
    // engine.setMesh(Mesh::pyramid({1.0f, 0.5f, 0.0f}));     // orange

    engine.init(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        engine.drawFrame();
    }

    engine.cleanup();
    return 0;
}