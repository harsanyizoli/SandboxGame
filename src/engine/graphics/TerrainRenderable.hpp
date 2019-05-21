#ifndef TERRAINRENDERABLE_H
#define TERRAINRENDERABLE_H

#include "Mesh.h"
#include "shader.h"
#include "types.h"
#include "../utils/util.h"

#include <vector>

struct Vertex3D {
    float x, y, z;
};

class TerrainRenderable
{
public:
    unsigned int VAO;
private:
    //Mesh* mesh = nullptr;
    Shader* shader = nullptr;

    Transform3D trans;

    std::vector<Vertex3D> vertices;

    unsigned int VBO;

    void* data;
public:
    TerrainRenderable(){
        setTrans();
        loadShader(std::string("world"));
    }
    
    ~TerrainRenderable(){
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void Draw(glm::mat4 view){
        //INFO("Terrain Draw");
        //glEnable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        shader->use();

        shader->setMat4("projection", trans.projection);
        shader->setMat4("view", view);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        glBindVertexArray(0);
        //glDisable(GL_CULL_FACE);
    }
    
protected:
    void setTrans(){
        glm::mat4 model = glm::mat4(1.0f);
        trans.model = model;

        trans.projection = glm::perspective(glm::radians(45.0f), ASPECT_RATIO, 0.1f, 100.0f);
    }   

    void genMesh(int triangles_in_a_row, float** height_map){
        std::cout << vertices.size();
        for(int i = 0; i < triangles_in_a_row; i++){
            for(int j = 0; j < triangles_in_a_row; j++) {

                float x00 = triangles_in_a_row/2 - (int)i;
                float y00 = height_map[i + 1][j + 1];
                float z00 = triangles_in_a_row/2 - (int)j % triangles_in_a_row;

                float x01 = x00;
                float y01 = height_map[i +1][j];
                float z01 = z00 + 1;

                float x10 = x00 + 1;
                float y10 = height_map[i][j + 1];
                float z10 = z00;

                float x11 = x00 + 1;
                float y11 = height_map[i][j];
                float z11 = z00 + 1;

                //triangle 00 01 10

                Vertex3D v = {x00, y00, z00};
                //std::cout << v.x << " " << v.z << "\n";
                vertices.push_back(v);

                v = {x01, y01, z01};
                vertices.push_back(v);

                v = {x10, y10, z10};
                vertices.push_back(v);

                //triangle 01 11 10

                v = {x01, y01, z01};
                vertices.push_back(v);

                v = {x11, y11, z11};
                vertices.push_back(v);

                v = {x10, y10, z10};
                vertices.push_back(v);
            }
        }
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3D), &vertices[0], GL_STATIC_DRAW);
    
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)0);

        glBindVertexArray(0);
    }

    void loadShader(std::string name){
        shader = new Shader((get_shader_path() + name +".vert").c_str(), (get_shader_path() + name + ".frag").c_str());
    }
};

#endif