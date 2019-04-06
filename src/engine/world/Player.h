#ifndef PLAYER_H
#define PLAYER_H
//#include "GameObject.h"
#include "../../common.h"

class Player
{
private:

    const float SPEED = 10.0f;
    const float MouseSensitivity =  0.1f;
    const float YAW = -90.0f;
    const float PITCH =  0.0f;

    float Yaw = YAW;
    float Pitch = PITCH;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    glm::vec3 Up;

public:
    Player(glm::vec3 Pos , glm::vec3 Front) : position(glm::vec3(0.0f, 0.0f, 3.0f)), front(glm::vec3(0.0f, 0.0f, -1.0f)){
        position = Pos;
        front = Front;
    };

    Player(){
        position = glm::vec3(0.0f, 0.0f, 3.0f);
        front = glm::vec3(0.0f, 0.0f, -1.0f);
        WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    };
    ~Player();

    glm::vec3 getFront(){
        return front;
    }
    glm::mat4 getLookAt(){
        return glm::lookAt(position, position + front, Up);
    }
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
        {
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
        }
    private: 
        void updateCameraVectors()
        {
            // Calculate the new Front vector
            glm::vec3 Front;
            Front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Front.y = sin(glm::radians(Pitch));
            Front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front = glm::normalize(Front);
            // Also re-calculate the Right and Up vector
            Right = glm::normalize(glm::cross(front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            Up = glm::normalize(glm::cross(Right, front));
            std::cout << front.x << " " << front.y << " " << front.z << std::endl;
        }
};

Player::~Player()
{
}
#endif