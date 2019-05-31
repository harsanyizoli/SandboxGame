#ifndef PLAYER_H
#define PLAYER_H

#include "../common.h"
#include "../graphics/Camera.h"
#include "../event/window.hpp"
#include "../physics.hpp"
#include "Terrain.hpp"
#include "GameObject.h"

#include <vector>
struct JUMPATTR {
    bool jumping = false;
    float jumpHeight;
};
class Player : public Camera
{
public:
    glm::vec3 handPos = {0.0f, -0.15f, 0.4f};
    glm::vec3 weaponPos;
private:
    float height = 2.0f;
    float p_lastx = 640;
    float p_lasty = 360;
    JUMPATTR jumpAttrs;
    Physics::AABB bb = Physics::AABB({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});
    GameObject* weapon = nullptr;
    
public:
    Player(){
        Position = glm::vec3(0.0f, height, 0.0f);
        bb = Physics::AABB({-0.2f, 0.0f, -0.2f}, {0.2f, height, 0.2f});
    }
    
    ~Player(){   
    }

    void setWeapon(GameObject* g){
        weapon = g;
    }

    void apply(float g, float dt){
        if(jumpAttrs.jumping){
            //if(!(jumpAttrs.jumpHeight < 0.0f))
            Position.y += dt*jumpAttrs.jumpHeight;  
            jumpAttrs.jumpHeight +=  dt*g;
        } else {
            Position.y += dt*g;
        }

        float currentTerrainHeight = Terrain::getHeightForPos(Position.x , Position.z) + height;
        if(Position.y < currentTerrainHeight){
            Position.y = currentTerrainHeight;
            jumpAttrs.jumping = false;
        }
        bb.moveYto(Position.y);
        glm::vec3 wf;
        wf.x = Front.x * cos(0.174f) - Front.z * sin(0.174f);
        wf.z = Front.x * sin(0.174f) + Front.z * cos(0.174f);

        weaponPos = {Position.x + handPos.x + wf.x, 
                    Position.y + handPos.y + Front.y, 
                    Position.z + handPos.z + wf.z};
        weapon->move(weaponPos);
        weapon->rotateY(-1*Yaw-90.0f, handPos);
        weapon->rotateX(Pitch, handPos);
    }

    void handleInput(float dt){
        handleKeyInput(dt);
        handleMouseInput(dt);
    }
private:
    void handleKeyInput(float dt){
        float velocity = MovementSpeed * dt;
        if(Window::isKeyPressed(GLFW_KEY_W)){
            if(Window::isKeyPressed(GLFW_KEY_LEFT_SHIFT) ){
                velocity *= 5.0f;
            } else {
                MovementSpeed = BASE_SPEED;
            }
            Position.x += Front.x * velocity;
            Position.z += Front.z * velocity;
            keepInBoundary(Position.x, Position.z);
        }
        if(Window::isKeyPressed(GLFW_KEY_S)){
            Position.x -= Front.x * velocity;
            Position.z -= Front.z * velocity;
            keepInBoundary(Position.x, Position.z);
        }
        if(Window::isKeyPressed(GLFW_KEY_A)){
            Position.x -= Right.x * velocity;
            Position.z -= Right.z * velocity;
            keepInBoundary(Position.x, Position.z);
        }
        if(Window::isKeyPressed(GLFW_KEY_D)){
            Position.x += Right.x * velocity;
            Position.z += Right.z * velocity;
            keepInBoundary(Position.x, Position.z);
        }
        if(Window::isKeyPressed(GLFW_KEY_SPACE) && !jumpAttrs.jumping){
            jumpAttrs.jumping = true;
            jumpAttrs.jumpHeight = 8.0f;
        }
            bb.move({Position.x, 0.0f, Position.z});
            //Position.y = Terrain::getHeightForPos(Position.x , Position.z) + height;
            //std::cout << "x.: " << Position.x << "   z: " << Position.z << std::endl;
    }


    void handleMouseInput(float dt){
        float xoffset = Window::m_x - p_lastx;
        float yoffset = p_lasty - Window::m_y;
        //std::cout << xoffset << " " << yoffset << std::endl;

        p_lastx = Window::m_x;
        p_lasty = Window::m_y;

        ProcessMouseMovement(xoffset, yoffset);
    }
    void keepInBoundary(float x, float z){
        if (x >= 0 ) {
            if(x > 510.0f)
                Position.x = 510.0f;
        } else {
            if (x < -510.0f)
                Position.x = -510.0f;
        }
        if (z >= 0 ) {
            if(z > 510.0f)
                Position.z = 510.0f;
        } else {
            if (z < -510.0f)
                Position.z = -510.0f;
        }
        
    }
};

#endif

