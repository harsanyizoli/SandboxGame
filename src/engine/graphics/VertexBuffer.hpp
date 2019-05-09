#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "../common.h"
#include "types.h"

template<class T>
class VertexBuffer
{
private:

    GLuint vbo;

public:

    VertexBuffer(float* data, size_t size){
        genVertexBuffer(data, size);
    }

    ~VertexBuffer(){
        if(vbo != 0){
            std::cout << "vbo deleted" << std::endl;
            glDeleteBuffers(1, &vbo);
        }
    }
    
private:

    void genVertexBuffer(float* data, size_t size){
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, size * sizeof(T), data, GL_STATIC_DRAW);
    }
};

#endif