#ifndef ENGINE_H
#define ENGINE_H
#include "event/window.hpp"

class Engine
{
private:
    Window* e_window;
public:

    Engine();
    ~Engine();

    void init();
    void update();

    void start();

};
#endif