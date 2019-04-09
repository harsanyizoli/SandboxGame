#include "window.hpp"

Window::Window(const char* title, int width, int height, bool isFullscreen)
    : m_title(title), m_width(width), m_height(height), m_fullscrean(isFullscreen)
{
    init();
    std::cout << "[] Window created" << std::endl;
}

Window::~Window(){
    destroyWindow();
}

void Window::createContext(){
    glfwMakeContextCurrent(m_window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    std::cout << "[] Context created" << std::endl;
}

void Window::destroyWindow(){
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::init(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    if (!glfwInit())
        exit(-1);
    m_window = glfwCreateWindow(1600, 900, "m_title",
        m_fullscrean ? glfwGetPrimaryMonitor() : NULL, 
        NULL);
    if(m_window == 0)
        std::cout << "!! Window creation failed" << std::endl;
    glfwSwapInterval(1);

    glfwSetKeyCallback(m_window, key_callback);
}

GLFWwindow* Window::getWindow(){
    return m_window;
}

void Window::update(){
    //std::cout << m_window << std::endl;
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}
void Window::clear(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Window::close(bool shouldClose = false){
    m_shouldClose = shouldClose;
}
void Window::shouldClose(){
    if(m_shouldClose){
        glfwSetWindowShouldClose(m_window, m_shouldClose);
    }
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    std::cout << "keycallback\n";               
}