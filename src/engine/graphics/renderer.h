#ifndef RENDERER_H
#define RENDERER_H
#include <iostream>
#include "../common.h"
//#include "shader.h"
//#include "buffer.hpp"
#include "text_buffer.hpp"

namespace Renderer
{
    extern std::vector<TextBuffer*> text_buffer_ptrs;

    void draw_text_2d(TextBuffer* b);
    //void draw_3d(Buffer b);
    void draw_fps(float dt, float originx = 100.0f, float originy = 100.0f);
    
    void gen_text_buffer(char *text);


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
#endif