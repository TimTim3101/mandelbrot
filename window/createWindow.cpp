#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "createWindow.h"

Window::Window(int width, int height, const char* name)
{
    if (!glfwInit())
        throw std::runtime_error("Failed to init GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, name, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwDestroyWindow(window);
        glfwTerminate();
        throw std::runtime_error("Failed to init GLAD");
    }
}

bool Window::SetIcon(GLFWwindow* window, const char* path)
{
    int width, height, channels;
    unsigned char* pixels = stbi_load(path, &width, &height, &channels, 4);
    if (!pixels)
    {
        std::cerr << "Failed to load window icon\n";
        return false;
    }

    GLFWimage icon;
    icon.width = width;
    icon.height = height;
    icon.pixels = pixels;

    std::cout << "Image loaded: W=" << width << ", H=" << height << ", CH=" << channels << std::endl;

    glfwSetWindowIcon(window, 1, &icon);
    stbi_image_free(pixels);
    return true;
}

GLFWwindow* Window::get() const
{
    return window;
}

Window::~Window()
{
    if (window)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}
