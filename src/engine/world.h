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

struct ground
{
    float  y = 0.0;
    float getYforPos(glm::vec3 Pos){
        return y;
    }
};
struct object {

    float x;
    float y;
    float z;
    int id;
    char* name;

    object(char* name, int id){
        this->name = name;
        this-> id = id;

    }

};

class World
{
private:
public:
    std::vector<object> objects;
    
    World(){

    };

    void printStat(){
    }

    int make_obj(){
        object* t = new object("obj 1", obj_id);
        objects.push_back(*t);
        obj_id++;
        return t->id;
    }

    void get_obj(int id){
        for(object o : objects){
            if(o.id == id){
                std::cout << o.name << std::endl;
            }
        }
    }
};

#endif