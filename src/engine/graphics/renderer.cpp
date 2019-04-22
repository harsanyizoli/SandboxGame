
#include "renderer.h"
#include "../common.h"

void get_char_witdh(char input);
void make_char(float* data, float x, float y, char c);

int get_char_width(char input) {
    static const int lookup[128] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        4, 2, 4, 7, 6, 9, 7, 2, 3, 3, 4, 6, 3, 5, 2, 7,
        6, 3, 6, 6, 6, 6, 6, 6, 6, 6, 2, 3, 5, 6, 5, 7,
        8, 6, 6, 6, 6, 6, 6, 6, 6, 4, 6, 6, 5, 8, 8, 6,
        6, 7, 6, 6, 6, 6, 8,10, 8, 6, 6, 3, 6, 3, 6, 6,
        4, 7, 6, 6, 6, 6, 5, 6, 6, 2, 5, 5, 2, 9, 6, 6,
        6, 6, 6, 6, 5, 6, 6, 6, 6, 6, 6, 4, 2, 5, 7, 0
    };
    return lookup[input];
}

void make_char(float* data, float x, float y, char c){
    float* d = data;
    *(d++) = x - 5; *(d++) = y - 5;
    *(d++) = 0.0f; *(d++) = 0.0f;
    *(d++) = x - 5; *(d++) = y + 5;
    *(d++) = 0.0f; *(d++) = 0.0f;
    *(d++) = x + 5; *(d++) = y + 5;
    *(d++) = 0.0f; *(d++) = 0.0f;

    *(d++) = x - 5; *(d++) = y - 5;
    *(d++) = 0.0f; *(d++) = 0.0f;
    *(d++) = x + 5; *(d++) = y + 5;
    *(d++) = 0.0f; *(d++) = 0.0f;
    *(d++) = x + 5; *(d++) = y - 5;
    *(d++) = 0.0f; *(d++) = 0.0f;
}

void Renderer::draw_text_2d(const char* text){

}
void Renderer::draw_fps( float dt, float originx, float originy ){
    float fps = 1/dt;
    char fpsstr[7]; // fps = max xxxx.xx format + \0
    sprintf(fpsstr, "a");
    std::cout << fpsstr << " " << strlen(fpsstr) << std::endl;
    GLuint buffer = gen_text_buffer(originx, originy, 0, fpsstr);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 2));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES, 0, 10 * 6);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //gen buffer
    //set bufer data fpsstr
    //render triangles
    //draw char texture onto triangles
}
GLuint Renderer::gen_text_buffer(float x, float y, float n, char *text){
    int length = strlen(text);
    float* data = (float*)malloc(sizeof(float) * 6 * 4 * length);
    for(int i = 0; i < length; i++){
        make_char(data, x, y, text[i]);
    }
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4 * length, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return buffer;
}