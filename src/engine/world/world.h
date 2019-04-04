#ifndef WORLD_H
#define WORLD_H

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#include "GameObject.h"

#define WORLD_SIZE 128
#define MAX_Y 128/2
#define MIN_Y -(128/2)
#define MAX_X 128/2
#define MIN_X -(128/2)
#define ORIGIN {0, 0}

class World
{
private:
public:
    std::vector<GameObject*> objects;
    
    World(){

    };
    void update(){
        for(GameObject* g : objects){
            g->render();
        }
    }
    void makeObject(char* name, char* vert, char* frag){
        GameObject* obj = new GameObject(name, vert, frag);
        objects.emplace_back(obj);
    }

    void printStat(){
        for(GameObject* g : objects){
            g->printInfo();
        }
    }

};

#endif