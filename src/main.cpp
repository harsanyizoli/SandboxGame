//#include <glad/glad.h>
#include "glad.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "player.h"
#include "util.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void fpsCounter(double deltaTime);
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

Player player(glm::vec3(0.0f, 0.2f, 3.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;

float currentFrame, lastFrame, deltaTime;
float jumpDuration = 3.0f;
bool isJumping;
int squares = 25; // ^3

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }     
}
int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sandbox Game", NULL, NULL);
    if (!window)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);
   
    Shader blockShader("shaders/block_vertex.shader", "shaders/block_fragment.shader");
    Shader floorShader("shaders/floor_vertex.shader", "shaders/floor_fragment.shader");
    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    float vertices[] = {
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 
         1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,

        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 
         1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 1.0f, 0.0f, 1.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
        6, 5, 4,
        6, 4, 7,
        1, 5, 2,
        6, 2, 5,
        4, 0, 3,
        3, 7, 4,
        2, 6, 7,
        2, 7, 3,
        1, 5, 4,
        1, 4, 0
    };
        
    unsigned int VBO1, VAO, ebo;

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &ebo);

    glBindVertexArray(VAO);
        
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texarrayture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    load_png_texture("textures/awesomeface.png");
    
    blockShader.use();
    blockShader.setInt("ourTexture", 0);/*
    float aFloor[] = {
        -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 
         1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 
         1.0f,  0.0f, 1.0f,   1.0f, 1.0f, 
        -1.0f,  0.0f, 1.0f,   1.0f, 0.0f
    };

    unsigned int VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aFloor), aFloor, GL_STATIC_DRAW);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
    // texture coord attribute
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(3);
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    load_png_texture("textures/floor.png");
    floorShader.use();
    floorShader.setInt("ourtexture", 1);*/
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFrontFace(GL_CW);
    //glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
    
    while (!glfwWindowShouldClose(window))
    {     
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        fpsCounter(deltaTime);

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT); 
    
        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(player.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 300.0f);
        blockShader.setMat4("projection", projection);
    
        // camera/view transformation
        glm::mat4 view = player.GetViewMatrix();
        blockShader.setMat4("view", view);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        blockShader.use();
        // render boxes
        glBindVertexArray(VAO);/*
        for (unsigned int i = 0; i < squares; i++)
        {
            for (unsigned int j = 0; j < squares; j++){
                for (unsigned int k = 0; k < squares; k++){
                    glm::mat4 model = glm::mat4(1.0f);
                    
                            model = glm::translate(model, glm::vec3((float)j*2, (float)i*2, (float)k*2));
                            //float angle = 20.0f * i;
                            //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                            //model = glm::rotate(model, glm::radians((float)glfwGetTime() * 100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                            //model = glm::rotate(model, glm::radians((float)glfwGetTime() * 100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                            //model = glm::translate(model, glm::vec3(sin((float)glfwGetTime() * 10.0f), cos((float)glfwGetTime() * 10.0f), 0.0f));
                            blockShader.setMat4("model", model);
                            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                }
            }
        }
        */
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        blockShader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 100);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window)
    {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player.ProcessKeyboard(RIGHT, deltaTime);
    /*
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        if(isJumping){
            return;
        } else {
            isJumping = true;
        }
        float start = glfwGetTime();
        float duration = start = float(glfwGetTime());
        std::cout << duration << std::endl;
        if(duration < 0.5f){
            camera.jump(true, deltaTime/ 10);
        } else if( duration >= 0.5 && duration <= jumpDuration){
            camera.jump(false, deltaTime / 10);
        }; 
        isJumping = false;
    }  */
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

    player.ProcessMouseMovement(xoffset, yoffset);
}
void fpsCounter(double deltaTime){
    double fps = 1 / deltaTime;
    std::cout << "FPS " << fps << std::endl;
}
