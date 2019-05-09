#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../common.h"

#include "../graphics/renderable.hpp"
#include <vector>

typedef struct {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
} Position;

class GameObject : public Renderable
{
public:
    
private:
    unsigned int id;
    const char* g_name; 
    
    std::string shaderName = "block";
    Position p;

    float rotateDegree = 0.0f;
    float scale = 0.50f;

public:
    GameObject(std::string model, std::string shader, const char* name = "Unnamed");
    ~GameObject();
    void move(Position toPos);
};

#endif