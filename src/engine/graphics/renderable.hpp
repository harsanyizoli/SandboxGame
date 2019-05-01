#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "../common.h"
#include <vector>

#define ASPECT_RATIO (float)16.0/9.0

struct Transformations {
    glm::mat4 perspective;// = glm::perspective(glm::radians(camera.zoom), ASPECT_RATIO, 0.1f, 100.0f);
    glm::mat4 view;// = camera.GetViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
} transform;
class Renderable
{
private:
    std::vector<float> vertices;
    std::vector<float> normal;
    std::vector<float> uv;

    std::vector<int> indices;

    GLuint vao;
    GLuint vbo;

public:
    Renderable(/* args */){
        glGenVertexArrays(1, &vao);
    }
    ~Renderable(){
        glDeleteVertexArrays(1, &vao);
    }
};

#endif