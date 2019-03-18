#ifndef BLOCK_H
#define BLOCK_H

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glad.h"
#include "shader.h"

class Block {
    Shader shader = Shader("shaders/block_vertex.shader", "shaders/block_fragment.shader");
    Player player;
    public:
        Block(glm::vec3 worldPos, Player player){
            worldPosition = worldPos;
            player = player;
        }

        void setPosition(glm::vec3 Pos){
            worldPosition = Pos;
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
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // texarrayture coord attribute
            //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
            //glEnableVertexAttribArray(1);
            shader.use();
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        void render(unsigned int VAO){
            glm::mat4 projection = glm::perspective(glm::radians(player.Zoom), 16.0f / 9.0f, 0.1f, 300.0f);
            shader.setMat4("projection", projection);

            glm::mat4 view = player.GetViewMatrix();
            shader.setMat4("view", view);

            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, worldPosition);
            shader.use();
            shader.setMat4("model", model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            glDrawArrays(GL_TRIANGLES, 0, 100);
        }

    private:

        glm::vec3 worldPosition;

        float vertices[24] = {
            -1.0f, -1.0f, -1.0f, 
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,  
            1.0f, -1.0f, 1.0f, 
            1.0f,  1.0f, 1.0f, 
            -1.0f,  1.0f, 1.0f,     
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
        1, 5, 4,
        1, 4, 0
    };

};
#endif