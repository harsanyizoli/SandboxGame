#include "buffer3d.hpp"
/*
Buffer3d::Buffer3d(float* data, int count){

    shader = new Shader((get_shader_path() + "block.vert").c_str(), (get_shader_path() + "block.frag").c_str());

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * count, data, GL_STATIC_DRAW);
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(position);
    //glEnableVertexAttribArray(normal);
    //glEnableVertexAttribArray(uv);
    glEnableVertexAttribArray(0);
}

Buffer3d::~Buffer3d()
{
}
void Buffer3d::bind(){
    glBindVertexArray(vao);
}
void Buffer3d::unbind(){
    glBindVertexArray(0);
}*/