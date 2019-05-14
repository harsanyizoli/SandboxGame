#ifndef TERRAINRENDERABLE_H
#define TERRAINRENDERABLE_H

#include "Mesh.h"
#include "shader.h"
#include "types.h"
#include "../utils/util.h"

#include <vector>

class TerrainRenderable
{
private:
    Mesh* mesh = nullptr;
    Shader* shader = nullptr;

    Transform3D trans;

    std::vector<Vertex> vertices {};
public:
    TerrainRenderable(){

    }
    
    ~TerrainRenderable(){

    }

    void Draw(glm::mat4 view){
        shader->use();

        shader->setMat4("projection", trans.projection);
        shader->setMat4("view", view);
        shader->setMat4("model", trans.model);

        mesh->Draw(*shader);
    }
    
protected:
    void setTrans(glm::vec3 pos){
        glm::mat4 model = glm::mat4(1.0f);
        trans.model = model;

        trans.projection = glm::perspective(glm::radians(45.0f), ASPECT_RATIO, 0.1f, 100.0f);
    }   
    void loadMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices){
        mesh = new Mesh(vertices, indices);
    }
};

#endif