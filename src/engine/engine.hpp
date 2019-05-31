#ifndef ENGINE_H
#define ENGINE_H
#include "event/window.hpp"
#include "world/World.h"
//#include "graphics/renderer.h"
#include "utils/util.h"
#include "graphics/ui.hpp"
#include <filesystem>

class Engine
{
public: 

private:
    struct Config
    {
        const int scr_width = 1280;
        const int scr_height = 720;
        const char* title = "Sandbox Game Demo";
        const bool fullscr = false;
    } config;
    
    Window* e_window;
    World* e_world;
    ui* e_ui;
public:

    Engine();
    ~Engine();

    void init();
    void update(float delta);

    void run();

    static double getTimer();

private:
    void chechForClose();
};
#endif