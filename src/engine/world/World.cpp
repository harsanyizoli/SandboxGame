#include "World.h"

World::World(){
    std::cout << "[] World created " << this << std::endl;
    w_player = new Player();
    std::cout << "[] Player created " << w_player << std::endl;
    init();
    std::cout << "[] Terrain created " << w_terrain << "\n";
}

void World::render(){
    Renderer::render_3d_forward<Terrain>(*w_terrain, *w_player);
    for(GameObject* g : gameObjects){
        Renderer::render_3d_forward<GameObject>(*g, *w_player);
    }
}

void World::update(float deltaTime){
    //update stuff and render them
    w_player->handleInput(deltaTime);
    w_player->apply(gravity, deltaTime);
    render();
}

void World::loadWorldFromFile(){

}

void World::init(){
    
    GameObject* g = new GameObject("nanosuit", "model", "obj 1");
    g->move({-100.0f, 0.0f, 0.0f});
    g->scale = 0.001f;
    gameObjects.push_back(g);

    g = new GameObject("sun", "model");
    g->move({-110.0f, 10.0f, 0.0f});
    g->scale = 100.0f;
    gameObjects.push_back(g);

    g = new GameObject("weapon", "model", "weapon");
    g->move(w_player->handPos);
    g->scale = 2.0f;
    w_player->setWeapon(g);
    gameObjects.push_back(g);
    
    w_terrain = new Terrain();
}
void World::initTerrain(){
}