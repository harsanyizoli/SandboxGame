#include "common.h"
#include "engine/engine.h"
#include "util.h"

float deltaTime, lastFrame;
FPS fps = {0, 0};

int main(int argc, char const *argv[])
{
    GLFWwindow* window = createContext();
    Engine* e = new Engine(window);
    World w = e->initialize_world();
    w.makeObject("obj1", "../../../shaders/block.vert", "../../../shaders/block.vert");
    
    while (!glfwWindowShouldClose(window))
    {     
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        updateFps(&fps, deltaTime);

        e->input_handler();
        //w.printStat();
        w.update();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT); 
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}
