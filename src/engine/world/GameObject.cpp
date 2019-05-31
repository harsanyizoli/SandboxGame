#include "GameObject.h"

GameObject::GameObject(std::string model, std::string shader, const char* name)
    : g_name(name)
    {
    std::cout << "[] Loading model... " << model << "\n";
    loadModel(model);
    loadShader(shader);
}

void GameObject::move(glm::vec3 toPos){
    setModel(toPos, scale);
}

void GameObject::setScale(float s){
    scale = s;
}

void GameObject::rotateX(float deg, glm::vec3 offset){
    rotatexModel(deg, offset);
}

void GameObject::rotateY(float deg, glm::vec3 offset){
    rotateyModel(deg, offset);
}

void GameObject::rotateZ(float deg, glm::vec3 offset){
    rotatezModel(deg, offset);
}