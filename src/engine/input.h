#ifndef INPUT_H
#define INPUT_H
#include <iostream>
#include "../common.h"

int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 576;

int data = 0;

float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;
bool isJumping = false;
bool fullScreen = false;
void processInput(GLFWwindow *window)
    {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, 87) == GLFW_PRESS){
        //World->queryCurrentPlayer().ProcessKeyboard(FORWARD, deltaTime);
        std::cout << "W" << std::endl;
        //World::printStat();
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        //World.queryCurrentPlayer().ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        //World.queryCurrentPlayer().ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        //World.queryCurrentPlayer().ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        //World.queryCurrentPlayer().setMovementSpeed(20.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){
        //World.queryCurrentPlayer().setMovementSpeed(5.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS){
        //printf("Front: %f, %f, %f", player.Front.x, player.Front.y, player.Front.z);
        //printf("Pos: %f %f %f\n", player.Position.x, player.Position.y, player.Position.z);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) && !isJumping){
        isJumping = true;
        //player.jump(deltaTime);
        isJumping = false;
    }
        
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    //World->queryCurrentPlayer().ProcessMouseMovement(xoffset, yoffset);
}
#endif