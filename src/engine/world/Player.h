#ifndef PLAYER_H
#define PLAYER_H

#include "../common.h"
#include "../graphics/Camera.h"
#include "../event/window.hpp"

#include <vector>

class Player : public Camera
{
private:
    float height;

    float p_lastx = 640;
    float p_lasty = 360;
    
public:
    Player(){
    }
    ~Player(){   
    }
    void handleInput(float dt){
        handleKeyInput(dt);
        handleMouseInput(dt);
    }
private:
    void handleKeyInput(float dt){
        if(Window::isKeyPressed(GLFW_KEY_W)){
            if(Window::isKeyPressed(GLFW_KEY_LEFT_SHIFT) ){
                MovementSpeed = 20.0f;
            } else {
                MovementSpeed = BASE_SPEED;
            }
            ProcessKeyboard(FORWARD, dt);
        }
        if(Window::isKeyPressed(GLFW_KEY_S)){
            ProcessKeyboard(BACKWARD, dt);
        }
        if(Window::isKeyPressed(GLFW_KEY_A)){
            ProcessKeyboard(LEFT, dt);
        }
        if(Window::isKeyPressed(GLFW_KEY_D)){
            ProcessKeyboard(RIGHT, dt);
        }
    }


    void handleMouseInput(float dt){
        float xoffset = Window::m_x - p_lastx;
        float yoffset = p_lasty - Window::m_y;
        //std::cout << xoffset << " " << yoffset << std::endl;

        p_lastx = Window::m_x;
        p_lasty = Window::m_y;

        ProcessMouseMovement(xoffset, yoffset);
    }
};

#endif

