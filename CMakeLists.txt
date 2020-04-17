cmake_minimum_required(VERSION 3.12)

project(render2 VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

add_executable(render2 main.cpp HelloTriangleApplication.cpp HelloTriangleApplication.h)
target_link_libraries(render2 Vulkan::Vulkan glfw glm::glm)
