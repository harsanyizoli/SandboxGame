#include "world.h"

World::World(){
    std::cout << "[] World created" << std::endl;
    w_player = new Player();
    std::cout << "[] Player created " << w_player << std::endl;
    init();
}

void World::render(){
    //std::cout << "render" << std::endl;
    for(GameObject* g : gameObjects){
        g->render(w_player);
        //std::cout << w_player->Zoom << std::endl;
    }
}

void World::update(float deltaTime){
    //update stuff and render them
    handlePlayerKeys(deltaTime);
    handlePlayerMouse(deltaTime);
    //getPlayerPos();
    render();
}

void World::loadWorldFromFile(){
}

void World::getPlayerPos(){
    std::cout << w_player->getPos().x << " " << w_player->getPos().z << std::endl;
}
void World::handlePlayerKeys(float dt){
    if(Window::isKeyPressed(GLFW_KEY_W)){
        w_player->ProcessKeyboard(FORWARD, dt);
    }
    if(Window::isKeyPressed(GLFW_KEY_S)){
        w_player->ProcessKeyboard(BACKWARD, dt);
    }
    if(Window::isKeyPressed(GLFW_KEY_A)){
        w_player->ProcessKeyboard(LEFT, dt);
    }
    if(Window::isKeyPressed(GLFW_KEY_D)){
        w_player->ProcessKeyboard(RIGHT, dt);
    }
}
void World::handlePlayerMouse(float dt){

    //std::cout << p_lastx << " " << p_lasty << std::endl;
    float xoffset = Window::m_x - p_lastx;
    float yoffset = p_lasty - Window::m_y;
    //std::cout << xoffset << " " << yoffset << std::endl;

    p_lastx = Window::m_x;
    p_lasty = Window::m_y;

    w_player->ProcessMouseMovement(xoffset, yoffset);
}
void World::init(){
    GameObject* g = new GameObject("obj 1");
    gameObjects.push_back(g);
}