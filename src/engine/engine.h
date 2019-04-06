#include "event/input.h"
#include "graphics/text.h"
#include "log.h"
#include "world/world.h"
#include "event/window.hpp"

class Engine
{
private:
    Window* window;
    World* world;
    
public:
    Engine(){
        window = new Window("Sandbox Game", 1600, 900);
    };
    
    ~Engine();


    void input_handler(){
        processInput(window->getWindow());
    }

    World initialize_world(){
        world = new World();
        return *world;
    }

    void update(){
        world->update();
        window->update();
        std::cout << "engine.update();" << std::endl;
    }

};