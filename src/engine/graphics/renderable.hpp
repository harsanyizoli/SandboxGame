#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "../common.h"
#include "../utils/util.h"
#include "types.h"
#include "shader.h"
#include "Mesh.h"
#include "Model.h"

#include <vector>

class Renderable
{

private:

    Model* model;
    Shader* shader;

    Transform3D trans;

public:
    Renderable(){
        INFO("Renderable constructor");
        trans.projection = glm::perspective(glm::radians(45.0f), ASPECT_RATIO, 0.1f, 100.0f);
    }

    ~Renderable(){

    }

    void Draw(glm::mat4 view){
        shader->use();

        shader->setMat4("projection", trans.projection);
        shader->setMat4("view", view);
        shader->setMat4("model", trans.model);

        model->Draw(*(this->shader));
    }

protected:

    void setModel(glm::vec3 pos, float scale, float rotate){
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        model = glm::scale(model, glm::vec3(scale));
        model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 1.0f, 0.0f));
        trans.model = model;
    }   
    void loadModel(std::string name){
        model = new Model((char*)(get_model_path() + name + ".obj").c_str()); 
    }
    void loadShader(std::string name){
        shader = new Shader((get_shader_path() + name +".vert").c_str(), (get_shader_path() + name + ".frag").c_str());
    }
};


#endif