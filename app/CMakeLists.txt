set(SOURCE_LIST
	main.cpp
        )
add_executable(render_app ${SOURCE_LIST})
target_include_directories(render_app PUBLIC ../include ../)
set_target_properties(render_app PROPERTIES CXX_STANDARD 17)
set(LIBRARY_LIST Vulkan::Vulkan glfw glm::glm render2)

target_link_libraries(render_app
        ${LIBRARY_LIST})
install(
TARGETS render_app
RUNTIME DESTINATION bin
)