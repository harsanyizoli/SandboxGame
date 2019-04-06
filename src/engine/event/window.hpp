#include "../../common.h"

class Window
{
private:
    char* m_title;
    int m_width;
    int m_height;
    bool m_fullscrean;

    GLFWwindow* m_window;

public:
    Window(char* title, int width, int height);
    ~Window();

    GLFWwindow* getWindow();
    void update();
};
