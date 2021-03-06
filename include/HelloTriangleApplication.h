#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <optional>
#define NVVK_ALLOC_DEDICATED
#include <nvvk/extensions_vk.hpp>
#include <nvvk/allocator_vk.hpp>
#include <nvvk/debug_util_vk.hpp>
#include <nvvk/descriptorsets_vk.hpp>

// #VKRay
#include <nvvk/raytraceKHR_vk.hpp>


#include <iostream>
#include <vector>
#include <fstream>
#include <array>

#include <Square.h>
#include <VikingRoom.h>
#include <VertexBufferCreator.h>
#include <UniformBufferCreator.h>
#include <IndexBufferCreator.h>
#include <TextureBufferCreator.h>

#include "Context.h"


class HelloTriangleApplication final {
public:
  void setup(VkInstance &_instance, VkDevice &_device, VkPhysicalDevice & _physicalDevice, VkQueue &_graphicsQ, VkQueue &_presentQ) {
    // Initialize function pointers
    vk::DynamicLoader         dl;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
      dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
    VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);
    VULKAN_HPP_DEFAULT_DISPATCHER.init(_instance);
    VULKAN_HPP_DEFAULT_DISPATCHER.init(_device);

    m_instance = _instance;
    m_device = _device;
    m_physicalDevice = _physicalDevice;
    m_graphicsQueue = _graphicsQ;
    m_presentQueue = _presentQ;


    m_alloc.init(m_device, m_physicalDevice);

    //m_queue = m_device.getQueue(m_graphicsQueueIndex, 0);
    //m_cmdPool = m_device.createCommandPool({ vk::CommandPoolCreateFlagBits::eResetCommandBuffer, graphicsQueueIndex });
    //m_pipelineCache = device.createPipelineCache(vk::PipelineCacheCreateInfo());
  }

  void initVulkan();

  void run()
  {
    mainLoop();
  }
  void initWindow();
  VkSurfaceKHR createSurface(VkInstance &);
  void createSwapChain(SwapChainSupportDetails&, QueueFamilyIndices &);

  void createGraphicsPipeline();
  void createRenderPass();
  void createFramebuffers();
  void createCommandPool(QueueFamilyIndices&);
  void createCommandBuffers();
  void createSyncObjects();
  void createVertexBuffer();
  void createIndexBuffer();
  void createBuffer(VkDeviceSize, VkBufferUsageFlags, VkMemoryPropertyFlags, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void createImageViews();
  void createDescriptorSetLayout();
  void createDepthResources();
  void createRayTracing(int graphicsQueueIdx);
  void createUniformBuffers();
  void createTextureImage();
  void createTextureImageView();
  void createTextureSampler();
  void createDescriptorPool();
  void createDescriptorSets();
  void loadModel();


  nvvk::RaytracingBuilderKHR::Blas objectToVkGeometryKHR();
  void createBottomLevelAS();
  void createTopLevelAS();

  void cleanup();

  GLFWwindow* window;
  VkSurfaceKHR m_surface;
private:
  VkInstance m_instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  vk::PhysicalDevice m_physicalDevice;
  vk::PhysicalDeviceRayTracingPropertiesKHR  m_rtProperties;
  nvvk::RaytracingBuilderKHR m_rtBuilder;

  nvvk::AllocatorDedicated m_alloc;  // Allocator for buffer, images, acceleration structures

  vk::Device m_device;


  VkSwapchainKHR swapChain;
  std::vector<VkImage> swapChainImages;
  VkFormat swapChainImageFormat;
  VkExtent2D swapChainExtent;
  std::vector<VkImageView> swapChainImageViews;

  VkRenderPass renderPass;
  VkDescriptorSetLayout descriptorSetLayout;

  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;

  std::vector<VkFramebuffer> swapChainFramebuffers;

  VkCommandPool commandPool;
  std::vector<VkCommandBuffer> commandBuffers;

  const int MAX_FRAMES_IN_FLIGHT = 2;
  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;

  std::vector<VkFence> imagesInFlight;
  size_t currentFrame = 0;

  
  std::vector<VkBuffer> uniformBuffers;
  std::vector<VkDeviceMemory> uniformBuffersMemory;

  VkDescriptorPool descriptorPool;

  std::vector<VkDescriptorSet> descriptorSets;
  VkImage textureImage;
  VkDeviceMemory textureImageMemory;
  VkImageView textureImageView;

  VkSampler textureSampler;

  VkImage depthImage;
  VkDeviceMemory depthImageMemory;
  VkImageView depthImageView;

  ModelBase<VikingRoom, uint32_t> model;
  BufferCreatorBase<VertexBufferCreator> vtxBuffer;
  BufferCreatorBase<UniformBufferCreator> uniformBuffer;
  BufferCreatorBase<IndexBufferCreator> idxBuffer;
  BufferCreatorBase<TextureBufferCreator> texBufferCreator;

  VkQueue m_presentQueue;
  VkQueue m_graphicsQueue;

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

  

  VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) const;

  void mainLoop();

  void cleanupSwapChain();
  void recreateSwapChain();

  VkCommandBuffer beginSingleTimeCommands();
  void endSingleTimeCommands(VkCommandBuffer commandBuffer);
  void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);



  void updateUniformBuffer(uint32_t currentImage);

  VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

  VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
  VkFormat findDepthFormat();
  bool hasStencilComponent(VkFormat format);

  void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
  void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
  void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

  uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);


  void drawFrame();
  VkShaderModule createShaderModule(const std::vector<char>& code);

  static std::vector<char> readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
      std::string output("failed to open file: ");
      output = output + filename;
      throw std::runtime_error(output);
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
  }
};

