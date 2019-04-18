#ifndef ENGINE_H
#define ENGINE_H
#include "event/window.hpp"
#include "world/world.h"
#include "graphics/renderer.h"
class Engine
{
public: 
    const int scr_width = 1280;
    const int scr_height = 720;
private:
    Window* e_window;
    World* e_world;

public:

    Engine();
    ~Engine();

    void init();
    void update(float delta);

    void start();
private:
    void chechForClose();
};
#endif