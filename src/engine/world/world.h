#ifndef WORLD_H
#define WORLD_H

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#include "GameObject.h"
#include "Player.h"

#define WORLD_SIZE 128
#define MAX_Y 128/2
#define MIN_Y -(128/2)
#define MAX_X 128/2
#define MIN_X -(128/2)
#define ORIGIN {0, 0}

class World
{
public:
    std::vector<GameObject*> gameObjects;
    Player player = Player();
    World(){}

    void update(){
        for(GameObject* g : gameObjects){
            g->render();
            std::cout << "g->render(player.getLookAt()) " << g->printInfo() << std::endl;
        }
        std::cout << "wordupdate() " << gameObjects.size() << std::endl;
    }

    void makeObject(const char* name,const char* vert,const char* frag){
        GameObject* obj = new GameObject(name, vert, frag);
        gameObjects.emplace_back(obj);
        std::cout << "object added" << obj->printInfo() << std::endl;
    }

    void printStat(){
        for(GameObject* g : gameObjects){
            g->printInfo();
        }
    }

};

#endif