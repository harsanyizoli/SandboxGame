#include "../common.h"

class Buffer
{
public:
    GLuint vao;
    GLuint vbo;
private:
    /* data */
public:
    Buffer(/* args */);
    ~Buffer();

    void bind();
    void unbind();
private:

};

Buffer::Buffer(/* args */)
{
}

Buffer::~Buffer()
{
}
void Buffer::bind(){
    glBindVertexArray(vao);
}
void Buffer::unbind(){
    glBindVertexArray(0);
}