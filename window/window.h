#ifndef WINDOW_H
#define WINDOW_H

#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

class Window {
  private:
    GLFWwindow *window = nullptr;

  public:
    Window(int width, int height, const char *name);
    ~Window();

    GLFWwindow *get() const;
};

#endif
