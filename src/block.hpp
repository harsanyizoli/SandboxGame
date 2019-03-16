#ifndef BLOCK_H
#define BLOCK_H

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glad.h"
#include "shader.h"

class Block {

    public:
        Block(glm::vec3 worldPos){
            worldPosition = worldPos;
        }

        void setPosition(glm::vec3 Pos){
            worldPosition = Pos;
        };
        Shader setShader(char* vertexshader, char* fragmentshader){
            Shader blockShader(vertexshader, fragmentshader);
            return blockShader;
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

            glBindBuffer(GL_ARRAY_BUFFER, 0);
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