#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../common.h"

#include "../graphics/shader.h"
//#include "../graphics/model.h"
#include "../graphics/buffer3d.hpp"
#include <vector>

typedef struct {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
} Position;

class GameObject
{
public:
    Buffer3d* buffer;
private:
    unsigned int id;
    const char* g_name; 
    
    std::vector<Position> data;

public:
    GameObject(const char* name = "Unnamed");
    ~GameObject();

};

#endif