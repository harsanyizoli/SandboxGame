#ifndef WORLD_H
#define WORLD_H

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#define WORLD_SIZE 128
#define MAX_Y 128/2
#define MIN_Y -(128/2)
#define MAX_X 128/2
#define MIN_X -(128/2)
#define ORIGIN {0, 0}

int obj_id = 0;

class World
{
private:
public:
    //std::vector<object> objects;
    
    World(){

    };

    void printStat(){
    }

};

#endif