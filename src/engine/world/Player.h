#ifndef CAMERA_H
#define CAMERA_H

#include "../common.h"
#include <vector>

// Defines several possible options for Player movement. Used as abstraction to stay away from window-system specific input methods
enum Player_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default Player values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  50.0f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;
const float GRAVITY     = -10.0f;
//float velo = 5.0f;

// An abstract Player class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Player
{
public:
    // Player Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler Angles
    float Yaw;
    float Pitch;
    // Player options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // Constructor with vectors
    Player(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // Constructor with scalar values
    Player(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of Player defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Player_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * glm::vec3(velocity, 0.0f, velocity);
        if (direction == BACKWARD)
            Position -= Front * glm::vec3(velocity, 0.0f, velocity);
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }
    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        if(abs(xoffset) >= 600 || abs(yoffset) >= 300){
            xoffset = 0;
            yoffset = 0;
        }
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // Update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
        //std::cout << Front.x << " " << Front.y << " " << Front.z << std::endl;
    }

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        if (Zoom >= 1.0f && Zoom <= 45.0f)
            Zoom -= yoffset;
        if (Zoom <= 1.0f)
            Zoom = 1.0f;
        if (Zoom >= 45.0f)
            Zoom = 45.0f;
    }
    glm::vec3 getPos(){
        return Position;
    }
    void setMovementSpeed(float speed){
        MovementSpeed = speed;
    }
    /*
    void fall(float deltaTime){
        if(Position.y > 0.0f){
            Position.y = Position.y - (deltaTime * velo);
            velo = velo + GRAVITY * deltaTime;
        } else if (Position.y < 0.0f){
            Position.y = 0.0f;
        }
    }
    
    void jump (float deltaTime){
        duration += deltaTime;
        //printf("y: %f, d: %f\n", Position.y, duration);
        if(checkPosy()){
            Position.y = Position.y + (velo * deltaTime);  
        }
        velo = velo + GRAVITY * deltaTime;  
        if(Position.y < 0.0f){
            velo = 5.0f;
            Position.y = 0.0f;
        }
    }
    bool checkPosy(){
        if(Position.y >= 0.0f){
            return true;
        }
        return false;
    }*/
private:
    float duration = 0.0f;
    // Calculates the front vector from the Player's (updated) Euler Angles
    void updateCameraVectors()
    {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // Also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};
#endif

