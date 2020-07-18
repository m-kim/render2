cmake_minimum_required(VERSION 3.12)

project(render2 VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

# Need this to override the include path to Vulkan-Headers
get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
    set( USING_VULKANSDK "YES" PARENT_SCOPE) # PARENT_SCOPE important to have this variable passed to parent. Here we want to notify that something used the Vulkan package
else()
    set( USING_VULKANSDK "YES")
endif()

add_definitions(-DUSEVULKANSDK)
add_definitions(-DGLFW_INCLUDE_VULKAN)
add_definitions(-DVK_ENABLE_BETA_EXTENSIONS)

set(VULKAN_HEADERS_OVERRIDE_INCLUDE_DIR CACHE PATH "Override for Vulkan headers, leave empty to use SDK")
if (VULKAN_HEADERS_OVERRIDE_INCLUDE_DIR)
set(vulkanHeaderDir ${VULKAN_HEADERS_OVERRIDE_INCLUDE_DIR})
else()
set(vulkanHeaderDir ${VULKANSDK_INCLUDE_DIR})
endif()

include_directories(${vulkanHeaderDir})
file(GLOB vulkanHeaderFiles "${vulkanHeaderDir}/vulkan/vulkan.h")
LIST(APPEND PACKAGE_SOURCE_FILES ${vulkanHeaderFiles} )
source_group(Vulkan FILES  ${vulkanHeaderFiles} )
LIST(APPEND LIBRARIES_OPTIMIZED ${VULKAN_LIB} )
LIST(APPEND LIBRARIES_DEBUG ${VULKAN_LIB} )
set(VULKAN_HEADERS "<vulkan/vulkan_core.h>")
# Needed to override the include path to VULKAN_HEADERS


add_definitions(-DVULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1)

SET(${CMAKE_PROJECT_NAME}_SHADERS_DIR ${CMAKE_SOURCE_DIR})
SET(${CMAKE_PROJECT_NAME}_TEXTURE_DIR ${CMAKE_SOURCE_DIR}/models)
SET(${CMAKE_PROJECT_NAME}_MODEL_DIR ${CMAKE_SOURCE_DIR}/models)

configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/common/config.h.in"
            "${CMAKE_CURRENT_SOURCE_DIR}/config.h" )


function(add_spirv_shader SHADER_STAGE INPUT_FILE OUTPUT_FILE)
        add_custom_command(
                OUTPUT ${OUTPUT_FILE}
                COMMAND ${Vulkan_INCLUDE_DIRS}/../bin/glslc -fshader-stage=${SHADER_STAGE} ${INPUT_FILE} -o ${OUTPUT_FILE}
                MAIN_DEPENDENCY ${INPUT_FILE}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )
endfunction()

add_spirv_shader(vertex shader.vert vert.spv)
add_spirv_shader(fragment shader.frag frag.spv)

add_subdirectory(src)
add_subdirectory(app)