#ifndef RENDERER_H
#define RENDERER_H
#include <iostream>

namespace Renderer
{
    void draw_text_2d(const char* text);
    void draw_fps(float dt);
} // Renderer

void update();

void bindbuffer();
void draw3D(); //buffer

#endif