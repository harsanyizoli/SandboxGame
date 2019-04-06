#include "window.hpp"

Window::Window(char* title, int width, int height)
{
    if (!glfwInit()){
        std::cout << "[] window creation failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    std::cout << "[] Context created" << std::endl;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    m_window = window;
}

Window::~Window()
{
}

GLFWwindow* Window::getWindow() {
    return m_window;
}
void Window::update(){
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}
