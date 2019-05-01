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
    Player* w_player = nullptr;
    float p_lastx = 640;
    float p_lasty = 360;
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
};

#endif