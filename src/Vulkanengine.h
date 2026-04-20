
#ifndef RENDER_VULKANENGINE_H
#define RENDER_VULKANENGINE_H

#endif //RENDER_VULKANENGINE_H

#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <array>
#include <glm/gtc/matrix_transform.hpp>
#include "Vertex.h"
#include "Mesh.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"




struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};


// queue family indices
struct QueueFamilyIndices {
    int graphics = -1;
    int present = -1;
    bool isComplete() { return graphics >= 0 && present >= 0; }
};

// swapchain support details
struct SwapchainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class VulkanEngine {
public:
    void init(GLFWwindow* window);
    void drawFrame();
    void cleanup();
    void onMouseButton(int button, int action);
    void onMouseMove(double x, double y);
    void onScroll(double yOffset);
    void setMesh(const Mesh& mesh);
    void setMeshAtRuntime(const Mesh& mesh);

private:
    GLFWwindow* window;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSwapchainKHR swapchain;
    std::vector<VkImage> swapchainImages;
    VkFormat swapchainImageFormat;
    VkExtent2D swapchainExtent;
    std::vector<VkImageView> swapchainImageViews;
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    std::vector<VkFramebuffer> swapchainFramebuffers;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    void createVertexBuffer();
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    VkDescriptorSetLayout descriptorSetLayout;
    VkBuffer uniformBuffer;
    VkDeviceMemory uniformBufferMemory;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;
    VkDescriptorPool imguiDescriptorPool;
    void createDescriptorSetLayout();
    void createUniformBuffer();
    void updateUniformBuffer();
    void createDescriptorPool();
    void createDescriptorSets();
    void initImGui();
    void cleanupImGui();

    // instance
    void createInstance();
    bool checkValidationLayerSupport();

    // surface
    void createSurface();

    // device
    void pickPhysicalDevice();
    void createLogicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    // swapchain
    void createSwapchain();
    SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& modes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    // image views
    void createImageViews();

    // render pass
    void createRenderPass();

    // pipeline
    void createGraphicsPipeline();
    VkShaderModule createShaderModule(const std::vector<char>& code);
    static std::vector<char> readFile(const std::string& filename);

    // framebuffers
    void createFramebuffers();

    // commands
    void createCommandPool();
    void createCommandBuffers();

    // sync
    void createSyncObjects();

    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    void createIndexBuffer();

    // camera state
    float cameraTheta = 45.0f;   // horizontal angle
    float cameraPhi = 45.0f;     // vertical angle
    float cameraRadius = 3.0f;   // distance from target

    bool mousePressed = false;
    double lastMouseX = 0.0;
    double lastMouseY = 0.0;

    Mesh currentMesh;

    void createDepthResources();
    VkFormat findDepthFormat();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
};