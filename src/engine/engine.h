#include "event/input.h"
#include "graphics/text.h"
#include "log.h"
#include "world/world.h"

class Engine
{
private:
    GLFWwindow* window;
    World* world;
public:
    Engine(GLFWwindow* w){
        window = w;
    };
    
    ~Engine();

    void input_handler(){
        processInput(window);
    }

    World initialize_world(){
        world = new World();
        return *world;
    }

};