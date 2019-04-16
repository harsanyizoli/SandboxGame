#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../common.h"

#include "../graphics/shader.h"
//#include "../graphics/model.h"
#include "Player.h"
#include <vector>
typedef struct {
    float x;
    float y;
    float z;
} vertex;
class GameObject
{
private:
    Shader* g_shader = nullptr;
    //Model* g_model;
    unsigned int id;
    const char* g_name; 
    GLuint vao;
    //std::vector<vertex> vertices;
    float vertices[9] = { 
                        -1.0f, -1.0f, 0.0f,
                         0.0f,  1.0f, 0.0f,
                         1.0f, -1.0f, 0.0f
                        };
    
public:
    GameObject(const char* name);
    ~GameObject();
    void render(Player* player);
    void setupMesh();
};

#endif