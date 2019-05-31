#include "window.hpp"

bool Window::m_keys[MAX_KEYS];
bool Window::m_buttons[MAX_BUTTONS];
double Window::m_x;
double Window::m_y;
double Window::xoffset;
double Window::yoffset;
double Window::m_lastx;
double Window::m_lasty;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void error_callback(int error, const char* description);
bool firstMouse = true;

Window::Window(const char* title, int width, int height, bool isFullscreen)
    : m_title(title), m_width(width), m_height(height), m_fullscrean(isFullscreen)
{
    for(int i = 0; i < MAX_KEYS; i++){
        m_keys[i] = false;
    }
    for(int i = 0; i < MAX_BUTTONS; i++){
        m_buttons[i] = false;
    }
    m_x = m_width/2;
    m_y = m_height/2;
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
    if (!glfwInit())
        exit(-1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    m_window = glfwCreateWindow(m_width, m_height, m_title,
                                m_fullscrean ? glfwGetPrimaryMonitor() : NULL, 
                                NULL);
    if(m_window == 0)
        std::cout << "!! Window creation failed" << std::endl;
    glfwSwapInterval(1);
    std::cout << glfwGetVersionString() << std::endl;
    glfwSetKeyCallback(m_window, key_callback);
    glfwSetCursorPosCallback(m_window, cursor_position_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
    glfwSetErrorCallback(error_callback);
    //glfwSetWindowUserPointer(m_window, this);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

GLFWwindow* Window::getWindow(){
    return m_window;
}

void Window::update(){
    glfwSwapBuffers(m_window);
    glfwPollEvents();
    shouldClose();
}
void Window::clear(){
    glClearColor(0.1f, 0.0f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::close(bool shouldClose = false){
    m_shouldClose = shouldClose;
}
void Window::shouldClose(){
    if(m_shouldClose){
        glfwSetWindowShouldClose(m_window, m_shouldClose);
    }
}

bool Window::isKeyPressed(unsigned int keycode){
    if(keycode >= MAX_KEYS)
        return false;
    return m_keys[keycode];
}
bool Window::isButtonPressed(unsigned int button){
    if(button >= MAX_BUTTONS)
        return false;
    return m_buttons[button];
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    GLFWwindow* win = (GLFWwindow*)glfwGetWindowUserPointer(window);
    Window::m_keys[key] = action != GLFW_RELEASE;
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    Window::m_x = xpos;
    Window::m_y = ypos;
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    Window::m_buttons[button] = action != GLFW_RELEASE;
}
double Window::getCurrentTimer(){
    return glfwGetTime();
}
void error_callback(int error, const char* description){
    std::cout << error << " " << description << "\n";
}