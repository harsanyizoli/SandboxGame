#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H

#include <cstddef>
#include "../utils/util.h"
#include <vector>
#include "shader.h"
#include <lodepng.h>

typedef struct {
    GLfloat x;
    GLfloat y;

    GLfloat u;
    GLfloat v;
} vertex_2d;

typedef struct {
    GLuint program;
    Shader* shader;
    GLuint position;
    GLuint normal;
    GLuint uv;
    GLuint sampler;
    GLuint p_matrix;
    GLuint m_matrix;
    GLuint v_matrix;
} text_attributes;

class TextBuffer
{
public: 
    GLuint vao;
    GLuint vbo;
    GLuint texture;
    size_t size;
    char* ptr;
    std::vector<vertex_2d> vertices; 
    GLfloat origin_x = 100.0f, 
            origin_y = 100.0f;
    
    text_attributes ta;
private:

public:
    TextBuffer(size_t s);
    ~TextBuffer();
    
    void setTextToBeRendered();
    void bind();
    void unbind();

private:
    char* allocateBufferMemory(size_t size);
    void makeChar(std::string string);
    void genBuffers();
    void loadTexture(char* filename);
};

#endif