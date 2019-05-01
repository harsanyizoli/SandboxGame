#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include "../common.h"
#include "assert.h"
#include "../world/Player.h"

#include "buffer3d.hpp"
#include "text_buffer.hpp"

namespace Renderer
{
    extern std::vector<TextBuffer*> text_buffer_ptrs;

    void draw_text_2d(TextBuffer* b);
    //void draw_3d(Buffer b);
    void draw_fps(float dt, float originx = 100.0f, float originy = 100.0f);
    
    void gen_text_buffer(char *text);

    void render_3d(const Buffer3d& buffer, Player& p);
    
} // Renderer
#endif