#include <HelloTriangleApplication.h>
#include <Context.h>


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


  try {
    app.run(ctx.m_instance);
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }


  return EXIT_SUCCESS;
}