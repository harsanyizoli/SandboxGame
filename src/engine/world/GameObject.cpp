#include "GameObject.h"

GameObject::GameObject(std::string model, std::string shader, const char* name)
    : g_name(name)
    {
    std::cout << "gameobject constructor " << std::endl;
    loadModel(model);
    loadShader(shader);
    move({0.0f, -10.0f, 0.0f});
}

void GameObject::move(Position toPos){
    setModel({toPos.x, toPos.y, toPos.z}, scale, rotateDegree);
}