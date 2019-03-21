#ifndef BLOCK_H
#define BLOCK_H

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glad.h"
#include "shader.h"
#include "util.h"

class Block {
    Shader shader = Shader("shaders/block.vert", "shaders/block.frag");
    //Player player;
    public:
        Block(glm::vec3 worldPos){
            worldPosition = worldPos;
        }

        void setPosition(glm::vec3 Pos){
            worldPosition = Pos;
        }
        void setPlayerPos(glm::vec3 pos){

        }
        void genBlock(unsigned int VAO){

            unsigned int vbo, ebo;
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
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
            
            shader.use();
            shader.setInt("ourTexture", 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void render(unsigned int VAO, Player player){
            shader.use();

            glBindVertexArray(VAO);
            glm::mat4 projection = glm::perspective(glm::radians(player.Zoom), 16.0f / 9.0f, 0.1f, 300.0f);
            shader.setMat4("projection", projection);

            glm::mat4 view = player.GetViewMatrix();
            shader.setMat4("view", view);

            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, worldPosition);

            shader.setMat4("model", model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

    private:

        glm::vec3 worldPosition;

        float vertices[40] = {
            -1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
            1.0f,  1.0f, -1.0f, 1.0f, 0.0f,
            -1.0f,  1.0f, -1.0f, 0.0f, 0.0f,

            -1.0f, -1.0f, 1.0f,  0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
            1.0f,  1.0f, 1.0f, 1.0f, 0.0f,
            -1.0f,  1.0f, 1.0f, 0.0f, 0.0f
        };
        unsigned int indices[36] = {
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
        1, 4, 5,
        1, 0, 4
    };

};
#endif