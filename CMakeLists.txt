cmake_minimum_required(VERSION 3.12)

project(render2 VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

SET(${CMAKE_PROJECT_NAME}_SHADERS_DIR ${CMAKE_SOURCE_DIR})
SET(${CMAKE_PROJECT_NAME}_TEXTURE_DIR ${CMAKE_SOURCE_DIR}/textures)

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
set(render2_src
main.cpp HelloTriangleApplication.cpp)
set(render2_hdr 
HelloTriangleApplication.h)
add_executable(render2 ${render2_src} ${render2_hdr} vert.spv frag.spv)
target_link_libraries(render2 Vulkan::Vulkan glfw glm::glm)
