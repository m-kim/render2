cmake_minimum_required(VERSION 3.12)

find_package(glm REQUIRED)

set(imgui_hdr
 imgui/imgui.h
 imgui/imgui_internal.h
 imgui/imconfig.h
 imgui/imstb_rectpack.h
 imgui/imstb_textedit.h
 imgui/imstb_truetype.h
)
set(imgui_src 
 imgui/imgui.cpp
 imgui/imgui_demo.cpp
 imgui/imgui_draw.cpp
 imgui/imgui_widgets.cpp
)

project(render2 VERSION 0.1 LANGUAGES CXX)
add_executable(render2 main.cpp ${imgui_hdr} ${imgui_src})

