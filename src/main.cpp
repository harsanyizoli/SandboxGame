#include "engine/common.h"
#include "engine/engine.hpp"
#include "engine/utils/util.h"

float deltaTime, lastFrame;
FPS fps = {0, 0};

int main(int argc, char const *argv[])
{
    Engine game;
    game.start();
#if 0
    while (true)
    {     
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT); 
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        updateFps(&fps, deltaTime);

        e->update();
        //w.update();
    }
    return 0;
#endif
}
