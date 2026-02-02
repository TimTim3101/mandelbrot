cmake_minimum_required(VERSION 3.10)
project(mandelbrot)

set(CMAKE_CXX_STANDARD 17)

add_executable(mandelbrot
    mandelbrot.cpp
    shaders/shader.cpp
    window/createWindow.cpp
    /usr/src/glad/glad.c
)

find_package(glfw3 REQUIRED)

target_include_directories(mandelbrot PRIVATE
    shaders
    window
)

target_link_libraries(mandelbrot
    glfw
    GL
    dl
)
