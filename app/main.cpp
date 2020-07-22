#include <HelloTriangleApplication.h>
#include <Context.h>
#include <vulkan/vulkan.hpp>
VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

int main() {


  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

  std::cout << extensionCount << " extensions supported" << std::endl;

  std::vector<VkExtensionProperties> extensions(extensionCount);
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
  std::cout << "available extensions:" << std::endl;

  for (const auto& extension : extensions) {
    std::cout << "\t" << extension.extensionName << std::endl;
  }
  HelloTriangleApplication app;
  app.initWindow();

  Context ctx;
  ctx.createInstance();
  ctx.setupDebugMessenger();
  auto surf = app.createSurface(ctx.m_instance);
  ctx.pickPhysicalDevice(surf);
  ctx.createLogicalDevice(surf);
  app.setup(ctx.m_instance, ctx.m_device, ctx.m_physicalDevice, ctx.m_graphicsQueue, ctx.m_presentQueue);
  app.createSwapChain(ctx.m_details, ctx.m_indices);

  app.createImageViews();
  app.createRenderPass();
  app.createDescriptorSetLayout();
  app.createGraphicsPipeline();
  app.createDepthResources();
  app.createFramebuffers();
  app.createCommandPool(ctx.m_indices);
  app.initVulkan();
  app.createTextureImage();
  app.createTextureImageView();
  app.createTextureSampler();
  app.loadModel();
  app.createVertexBuffer();
  app.createIndexBuffer();
  app.createUniformBuffers();
  app.createDescriptorPool();
  if (!ctx.m_indices.graphicsFamily)
    exit(-1);
  app.createRayTracing(*ctx.m_indices.graphicsFamily);
  app.createBottomLevelAS();
  app.createTopLevelAS();

  app.createDescriptorSets();

  app.createCommandBuffers();
  app.createSyncObjects();


  try {
    app.run();
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  app.cleanup();

  vkDestroySurfaceKHR(ctx.m_instance, app.m_surface, nullptr);
  vkDestroyInstance(ctx.m_instance, nullptr);
  glfwDestroyWindow(app.window);

  glfwTerminate();




  return EXIT_SUCCESS;
}