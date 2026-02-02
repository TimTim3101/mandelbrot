#ifndef CREATE_WINDOW_H
#define CREATE_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
private:
    GLFWwindow* window = nullptr;

public:
    Window(int width, int height, const char* name);
    bool SetIcon(GLFWwindow* window, const char* path);
    ~Window();

    GLFWwindow* get() const;
};

#endif
