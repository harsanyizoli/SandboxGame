#ifndef WINDOW_H
#define WINDOW_H

#include "../common.h"

#define MAX_KEYS 512
#define MAX_BUTTONS 16

class Window
{
public:
    static bool m_keys[MAX_KEYS];
    static bool m_buttons[MAX_BUTTONS];
    static double m_x, m_y;
    static double xoffset, yoffset;
    static double m_lastx, m_lasty;

private:

    GLFWwindow* m_window;
    const char* m_title;
    unsigned int m_width;
    unsigned int m_height;
    bool m_fullscrean;
    bool m_shouldClose = false;
public:

    Window(const char* title, int width, int height, bool isFullscreen);
    ~Window();
    void update();
    void createContext();
    GLFWwindow* getWindow();
    void clear();
    void close(bool shouldClose);
    static bool isKeyPressed(unsigned int keycode);
    static bool isButtonPressed(unsigned int button);

private:
    friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void init();
    void shouldClose();
    void destroyWindow();
};
#endif