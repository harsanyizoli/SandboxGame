#ifndef WORLD_H
#define WORLD_H

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#include "Player.h"
#include "GameObject.h"
#include "../event/window.hpp"
#include "Terrain.hpp"
#include "../graphics/renderer.h"

class World
{
public:
    const char* name = "Test World";
private:

    glm::vec3 global_light = glm::vec3(0.0f, 10.0f, 0.0f);

    Player* w_player = nullptr;
    std::vector<GameObject*> gameObjects;
    Terrain* w_terrain = nullptr;

public:
    World();
    
    void loadWorldFromFile();

    void update(float deltaTime);
    void getPlayerPos();

    void handlePlayerKeys(float dt);
    void handlePlayerMouse(float dt);
    
private:
    void render();
    void init();

    void initTerrain();
};

#endif