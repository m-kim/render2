#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

#include <optional>
#include <iostream>

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;


  bool isComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

class Context
{
public:
  Context() = default;
  void createInstance();
  bool checkValidationLayerSupport();
  std::vector<const char*> getRequiredExtensions();
  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) const;
  void setupDebugMessenger();
  void pickPhysicalDevice(VkSurfaceKHR &);
  void createLogicalDevice(VkSurfaceKHR& surface);

  bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR &);

  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR &);
  SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR &);

  bool checkDeviceExtensionSupport(VkPhysicalDevice device);

  static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
  }

  VkInstance m_instance;
  VkDebugUtilsMessengerEXT m_debugMessenger;
  VkDevice m_device;
  VkQueue m_graphicsQueue, m_presentQueue;

  VkPhysicalDevice m_physicalDevice;
  SwapChainSupportDetails m_details;
  QueueFamilyIndices m_indices;

};

