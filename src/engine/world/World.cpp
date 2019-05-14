#include "World.h"

World::World(){
    std::cout << "[] World created " << this << std::endl;
    w_player = new Player();
    std::cout << "[] Player created " << w_player << std::endl;

    initTerrain();

    init();
}

void World::render(){
    //std::cout << "render" << std::endl;
    for(GameObject* g : gameObjects){
        Renderer::render_3d_forward<GameObject>(*g, *w_player);
    }
}

void World::update(float deltaTime){
    //update stuff and render them
    w_player->handleInput(deltaTime);
    //getPlayerPos();
    render();
}

void World::loadWorldFromFile(){

}

void World::init(){
    GameObject* g = new GameObject("nanosuit", "model", "obj 1");
    gameObjects.push_back(g);
    g = new GameObject("dj", "model");
    g->move({3.0f, 0.0f, 0.0f});
    gameObjects.push_back(g);
    g = new GameObject("tree", "model");
    g->move({0.0f, 0.0f, 4.0f});
    gameObjects.push_back(g);
}
void World::initTerrain(){
    w_terrain = new Terrain();
}