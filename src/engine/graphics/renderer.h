#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include "../common.h"
#include "assert.h"
#include "../world/Player.h"
#include "../world/GameObject.h"
#include "../world/Terrain.hpp"
#include <thread>

namespace Renderer
{
    //void draw_3d(Buffer b);
    void draw_fps(float dt, float originx = 100.0f, float originy = 100.0f);
    
    void gen_text_buffer(char *text);

    template<class T>
    void render_3d_forward(T& t, Player& p){
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        t.Draw(p.GetViewMatrix(), p.Position);
    }

} // Renderer
#endif