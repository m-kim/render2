set(SOURCE_LIST
    ../tinyobjloader/tiny_obj_loader.cc
    HelloTriangleApplication.cpp
        )
set(LIBRARY_LIST Vulkan::Vulkan glfw glm::glm)

add_library(render2 ${SOURCE_LIST})
target_include_directories(render2 PUBLIC ../ ../include )
set_target_properties(render2 PROPERTIES CXX_STANDARD 17)
target_link_libraries(render2
        ${LIBRARY_LIST})

