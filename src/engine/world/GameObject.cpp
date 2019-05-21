#include "GameObject.h"

GameObject::GameObject(std::string model, std::string shader, const char* name)
    : g_name(name)
    {
    std::cout << "gameobject constructor " << std::endl;
    loadModel(model);
    loadShader(shader);
}

void GameObject::move(Position toPos){
    setModel({toPos.x, toPos.y, toPos.z}, toPos.scale, toPos.rotate_degree);
}