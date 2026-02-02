#include "shaders/shader.h"
#include "window/createWindow.h"
#define MIN(a,b) (a < b) ? a : b

const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;
const double aspect = (double)WIN_WIDTH / WIN_HEIGHT;

double scale = 3.f;
double mouseX, mouseY;
double centerX, centerY;
double lastMouseX = .0f, lastMouseY = .0f;
bool dragging = false;

void framebuffer_size_callback(GLFWwindow * window, int width, int height) {
    glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    double zoom = (yoffset > 0) ? .9f : 1.1f;

    double beforeX = centerX + (mouseX / (double)WIN_WIDTH - .5f) * scale * aspect;
    double beforeY = centerY - (.5f - mouseY / (double)WIN_HEIGHT) * scale;

    scale *= zoom;

    double afterX = centerX + (mouseX / (double)WIN_WIDTH - .5f) * scale * aspect;
    double afterY = centerY - (.5f - mouseY / (double)WIN_HEIGHT) * scale;

    centerX += beforeX - afterX;
    centerY += beforeY - afterY;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static bool wasPressed = false;
    bool isPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    if (isPressed && !wasPressed) {
        lastMouseX = xpos;
        lastMouseY = ypos;
    }

    if (isPressed && wasPressed) {
        double dx = xpos - lastMouseX;
        double dy = ypos - lastMouseY;

        centerX -= dx / WIN_WIDTH * scale * aspect;
        centerY -= dy / WIN_HEIGHT * scale;

        lastMouseX = xpos;
        lastMouseY = ypos;
    }
    wasPressed = isPressed;

    mouseX = xpos;
    mouseY = ypos;
}

float vertices[] = {
    -1.f, -1.f,
     1.f, -1.f,
     1.f,  1.f,
    -1.f,  1.f
};

int main() {
    // Init window
    Window window(WIN_WIDTH, WIN_HEIGHT, "Mandelbrot");

    // Loading window icon
    window.SetIcon(window.get(), "../window/icon.png");

    GLuint VAO, VBO;

    // Init Vertex Buffer Object (VBO)
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Init Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Init shaders
    Shader shader("../shaders/shader.vert", "../shaders/shader.frag");

    // Callbacks
    glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);
    glfwSetScrollCallback(window.get(), scroll_callback);
    glfwSetCursorPosCallback(window.get(), mouse_callback);

    // Window
    while (!glfwWindowShouldClose(window.get())) {

        if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window.get(), GLFW_KEY_Q) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window.get(), true);
        }

        // Using shaders
        shader.use();

        // Clamps
        scale = MIN(scale, 3.f);
        scale = std::max(scale, 1e-6);

        // Uniforms
        glUniform1f(glGetUniformLocation(shader.getID(), "scale"), scale);
        glUniform1f(glGetUniformLocation(shader.getID(), "centerX"), centerX);
        glUniform1f(glGetUniformLocation(shader.getID(), "centerY"), centerY);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }
    // free RAM
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();

    return 0;
}
