set(SOURCE_LIST
    ../tinyobjloader/tiny_obj_loader.cc
    Context.cpp
    HelloTriangleApplication.cpp
    ../nv_shared_sources/nvvk/commands_vk.cpp
    ../nv_shared_sources/nvvk/debug_util_vk.cpp
    ../nv_shared_sources/nvvk/error_vk.cpp
    ../nv_shared_sources/nvvk/extensions_vk.cpp
    ../nv_shared_sources/nvh/nvprint.cpp
        )
set(HEADER_LIST
../include/BufferCreatorBase.h  
../include/HelloTriangleApplication.h  
../include/Square.h                
../include/Vertex.h
../include/Chalet.h             
../include/IndexBufferCreator.h        
../include/TextureBufferCreator.h  
../include/VertexBufferCreator.h
../include/Context.h            
../include/ModelBase.h                 
../include/UniformBufferCreator.h  
../include/VikingRoom.h
)
set(LIBRARY_LIST Vulkan::Vulkan glfw glm::glm)

add_library(render2 ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(render2 PUBLIC ../ ../include ../nv_shared_sources/)
set_target_properties(render2 PROPERTIES CXX_STANDARD 17)
target_link_libraries(render2
        ${LIBRARY_LIST})

