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
protected:
    bool isVisible = true;
private:

    Model* model = nullptr;
    Shader* shader = nullptr;

    Transform3D trans;

public:
    Renderable(){
        trans.projection = glm::perspective(glm::radians(45.0f), ASPECT_RATIO, 0.1f, 1500.0f);
        trans.model = glm::mat4(1.0f);
    }

    ~Renderable(){

    }

    void Draw(glm::mat4 view, glm::vec3 pos){
        if(isVisible) {
            shader->use();

            shader->setMat4("projection", trans.projection);
            shader->setMat4("view", view);
            shader->setMat4("model", trans.model);
            model->Draw(*shader);
        }
    }

protected:

    void setModel(glm::vec3 pos, float scale){
        trans.model = glm::translate(glm::mat4(1.0f), pos);
        //trans.model = glm::scale(trans.model, glm::vec3(scale));
    }

    void rotatexModel(float deg, glm::vec3 offset){
        trans.model = glm::translate(trans.model, -1.0f*offset);
        glm::vec3 anglex = glm::vec3(1.0f, 0.0f, 0.0f);
        trans.model = glm::rotate(trans.model, glm::radians(deg), anglex);
        trans.model = glm::translate(trans.model, offset);
    }
    
    void rotateyModel(float deg, glm::vec3 offset){
        trans.model = glm::translate(trans.model, -1.0f*offset);
        glm::vec3 angley = glm::vec3(0.0f, 1.0f, 0.0f);
        trans.model = glm::rotate(trans.model, glm::radians(deg), angley);
        trans.model = glm::translate(trans.model, offset);
    }

    void rotatezModel(float deg, glm::vec3 offset){
        trans.model = glm::translate(trans.model, -1.0f*offset);
        glm::vec3 anglez = glm::vec3(0.0f, 0.0f, 1.0f);
        trans.model = glm::rotate(trans.model, glm::radians(deg), anglez);
        trans.model = glm::translate(trans.model, offset);
    }

    void loadModel(std::string name){
        model = new Model(get_model_path() + name + ".obj");
    }

    void loadShader(std::string name){
        shader = new Shader((get_shader_path() + name +".vert").c_str(), (get_shader_path() + name + ".frag").c_str());
    }
    
};


#endif