#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../common.h"

#include "../graphics/renderable.hpp"
#include <vector>


class GameObject : public Renderable
{
public:
    glm::vec3 Position;
    float scale = 1.0f;
    float rotatex, rotatey, rotatez;
private:
    unsigned int id;
    const char* g_name; 

public:
    GameObject(std::string model, std::string shader, const char* name = "Unnamed");
    ~GameObject();
    void move(glm::vec3 toPos);
    void setScale(float s);
    void rotateX(float deg, glm::vec3 offset);
    void rotateY(float deg, glm::vec3 offset);
    void rotateZ(float deg, glm::vec3 offset);
};

#endif