#ifndef WINDOW_H
#define WINDOW_H

#include "../common.h"
#include "windowEvent.h"

class Window
{
private:

    GLFWwindow* m_window;
    //char* m_title;
    unsigned int m_width;
    unsigned int m_height;
    bool m_fullscrean;
    bool m_shouldClose = false;
    static bool keyPress[1024];

public:

    const char* m_title;
    Window(const char* title, int width, int height, bool isFullscreen);
    Window();
    ~Window();
    void update();
    void createContext();
    GLFWwindow* getWindow();
    void clear();
    void close(bool shouldClose);
    void shouldClose();

private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void init();
    void destroyWindow();
};
#endif