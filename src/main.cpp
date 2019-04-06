#include "common.h"
#include "engine/engine.h"
#include "util.h"

float deltaTime, lastFrame;
FPS fps = {0, 0};

int main(int argc, char const *argv[])
{
    //glfwSetCursorPosCallback(window, mouse_callback);
    Engine* e = new Engine();
    World w = e->initialize_world();
    w.makeObject("obj1", "/home/d/code/SandboxGame/shaders/block.vert", "/home/d/code/SandboxGame/shaders/block.frag");
    //w.makeObject("obj2", "/home/d/code/SandboxGame/shaders/block.vert", "/home/d/code/SandboxGame/shaders/block.frag");

    while (!glfwWindowShouldClose())
    {     
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT); 
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        updateFps(&fps, deltaTime);

        e->input_handler();
        e->update();
        //w.update();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}
