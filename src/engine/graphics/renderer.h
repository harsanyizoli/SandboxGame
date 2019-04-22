#ifndef RENDERER_H
#define RENDERER_H
#include <iostream>
#include "../common.h"
#include "shader.h"
namespace Renderer
{
    void draw_text_2d(const char* text);
    void draw_fps(float dt, float originx = 100.0f, float originy = 100.0f);
    
    GLuint gen_text_buffer(float x, float y, float n, char *text);

    struct Attrib
    {
        GLuint program;
        Shader* shader;
        GLuint position;
        GLuint normal;
        GLuint uv;
        GLuint sampler;
        GLuint projection_matrix;
        GLuint model_matrix;
        GLuint view_matrix;
    };
    
} // Renderer

void update();

void bindbuffer();
void draw3D(); //buffer

#endif