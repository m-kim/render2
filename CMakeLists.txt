cmake_minimum_required(VERSION 3.12)

find_package(glm REQUIRED)


project(render2 VERSION 0.1 LANGUAGES CXX)
add_executable(render2 main.cpp ${imgui_hdr} ${imgui_src})

