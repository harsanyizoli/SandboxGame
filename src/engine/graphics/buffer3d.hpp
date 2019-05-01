#ifndef BUFFER3D_H
#define BUFFER3D_H

#include "../common.h"
#include "../utils/util.h"
#include "shader.h"
//#include "model.h"
#include <vector>

class Buffer3d
{
public:
    GLuint vao;
    GLuint program;
    GLuint position = 0;
    GLuint normal = 1;
    GLuint uv = 2;

    GLuint sampler;
    GLuint projection_matrix;
    GLuint model_matrix;
    GLuint view_matrix;

    GLuint count;

    Shader* shader;

private:
    GLuint vbo;

public:
    Buffer3d(std::vector<float> , int count);
    ~Buffer3d();

    void bind();
    void unbind();
private:

};

#endif