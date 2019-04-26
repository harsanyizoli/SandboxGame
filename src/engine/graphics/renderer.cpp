
#include "renderer.h"

void get_char_witdh(char input);
void make_char(float* data, float x, float y, char c);

std::vector<TextBuffer*> Renderer::text_buffer_ptrs;

/*
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
*/

void Renderer::draw_text_2d(TextBuffer* b){
    
    b->bind();
    b->ta.shader->use();
    glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f); 
    b->ta.shader->setMat4("projection", projection);
    glm::mat4 model = glm::mat4(1.0f);
    b->ta.shader->setMat4("model", model);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, b->texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    b->unbind();
}
void Renderer::draw_fps( float dt, float originx, float originy ){
    TextBuffer* tb = new TextBuffer(16);
    Renderer::draw_text_2d(tb);
    //std::cout << "[] Rendering fps" << std::endl;
    //gen buffer
    //set bufer data fpsstr
    //render triangles
    //draw char texture onto triangles
}
void Renderer::gen_text_buffer(char *text){
    text_buffer_ptrs.emplace_back(new TextBuffer(16));
}