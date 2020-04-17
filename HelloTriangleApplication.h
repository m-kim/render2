#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>


#include <iostream>
#include <vector>
struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;

  bool isComplete() {
    return graphicsFamily.has_value();
  }
};

class HelloTriangleApplication final {
public:
  void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }

private:
  GLFWwindow* window;
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;

  static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
  }

  bool checkValidationLayerSupport();

  std::vector<const char*> getRequiredExtensions();

  void createInstance();

  void initWindow();
  void initVulkan();
  void pickPhysicalDevice();
  bool isDeviceSuitable(VkPhysicalDevice device);

  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) const;

  void setupDebugMessenger();

  void mainLoop();

  void cleanup();
};

