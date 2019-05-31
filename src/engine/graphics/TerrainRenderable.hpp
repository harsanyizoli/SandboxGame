#ifndef TERRAINRENDERABLE_H
#define TERRAINRENDERABLE_H

#include "Mesh.h"
#include "shader.h"
#include "types.h"
#include "../utils/util.h"
#include <lodepng.h>
#include <vector>


struct TerrainVertex {
    Vertex3D_pos v;
    Vertex3D_pos n;
    TexCoord2D_pos t;
};

class TerrainRenderable
{
public:
    unsigned int tVAO, wVAO, skyboxVAO;
private:
    //Mesh* mesh = nullptr;
    Shader* wShader = nullptr;
    Shader* tShader = nullptr;
    Shader* skyboxShader = nullptr;
    Transform3D trans;

    std::vector<TerrainVertex> terrainVertices;
    std::vector<TerrainVertex> waterVertices;

    unsigned int terrainVBO, waterVBO, skyboxVBO;
    unsigned int terrTextureId, terrSpecularId;
    unsigned int waterTextureId, waterSpecularId;
    unsigned int skyboxTextureId;

    std::vector<std::string> faces{
        "skybox/darkcity_rt.png",
        "skybox/darkcity_lf.png",
        "skybox/darkcity_up.png",
        "skybox/darkcity_dn.png",
        "skybox/darkcity_ft.png",
        "skybox/darkcity_bk.png"
    };

public:
    TerrainRenderable(){
        setTrans();
        wShader = loadShader(std::string("world"));
        tShader = loadShader(std::string("world"));
        skyboxShader = loadShader(std::string("skybox"));
        terrTextureId = TextureFromFile("tile_highres.png");
        terrSpecularId = TextureFromFile("tile_highres.png");
        waterTextureId = TextureFromFile("water_highres.png");
        waterSpecularId = TextureFromFile("water_highres.png");
        skyboxTextureId = loadCubemap(faces);

        tShader->use();
        tShader->setInt("material.diffuse", 0);
        tShader->setInt("material.specular", 1);
        tShader->setMat4("model", trans.model);
        tShader->setMat4("projection", trans.projection);
        tShader->setVec3("light.position", glm::vec3(-1000.0f, 10.0f, 0.0f));
        tShader->setVec3("light.ambient", 0.65f, 0.65f, 0.65f);
        tShader->setVec3("light.diffuse", 0.26f, 0.26f, 1.0f);
        tShader->setVec3("light.specular", 0.26f, 0.26f, 1.0f);
        tShader->setVec3("light.direction", -1.0f, -1.0f, 0.0f);

        wShader->use();
        wShader->setInt("material.diffuse", 2);
        wShader->setInt("material.specular", 3);
        wShader->setMat4("model", trans.model);
        wShader->setMat4("projection", trans.projection);
        wShader->setVec3("light.position", glm::vec3(-1000.0f, 10.0f, 0.0f));
        wShader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        wShader->setVec3("light.diffuse", 0.13f, 0.13f, 0.5f);
        wShader->setVec3("light.specular", 0.26f, 0.26f, 1.0f);
        //wShader->setVec3("light.direction", -1.0f, -1.0f, 0.0f);

        skyboxShader->use();
        skyboxShader->setInt("material.diffuse", 4);
        skyboxShader->setMat4("projection", trans.projection);
        //skyboxShader->setMat4("model", glm::mat4(1.0f));
        //glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 50.0f, 0.0f));
        //skyboxShader->setMat4("model", glm::scale(m, glm::vec3(256.0f, 500.0f, 256.0f)));
        skyboxShader->setMat4("model", glm::mat4(1.0f));

    }
    
    ~TerrainRenderable(){
        glDeleteBuffers(1, &terrainVBO);
        glDeleteBuffers(1, &waterVBO);
        glDeleteVertexArrays(1, &tVAO);
        glDeleteVertexArrays(1, &wVAO);
    }

    void Draw(glm::mat4 view, glm::vec3 position){
        //INFO("Terrain Draw");
        //glEnable(GL_CULL_FACE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //skybox
        glDepthMask(GL_FALSE);
        //glDepthFunc(GL_LEQUAL);
        skyboxShader->use();
        skyboxShader->setMat4("view", glm::mat4(glm::mat3(view)));
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureId);
        glBindVertexArray(skyboxVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthMask(GL_TRUE);

        tShader->use();
        tShader->setVec3("viewPos", position);
        tShader->setMat4("view", view);

        tShader->setFloat("material.shininess", 64.0f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, terrTextureId);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, terrSpecularId);

        glBindVertexArray(tVAO);
        glDrawArrays(GL_TRIANGLES, 0, terrainVertices.size());
        glBindVertexArray(0);

        wShader->use();
        wShader->setVec3("viewPos", position);
        wShader->setMat4("view", view);

        wShader->setFloat("material.shininess", 10.0f);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, waterTextureId);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, waterSpecularId);

        glBindVertexArray(wVAO);
        glDrawArrays(GL_TRIANGLES, 0, waterVertices.size());
        glBindVertexArray(0);
        //glDepthFunc(GL_LESS);
        //glDisable(GL_CULL_FACE);
    }
    
protected:
    void setTrans(){
        glm::mat4 model = glm::mat4(1.0f);
        trans.model = model;
        trans.projection = glm::perspective(glm::radians(45.0f), ASPECT_RATIO, 0.1f, 1000.0f);
    }   

    void genMesh(int triangles_in_a_row, float** height_map, float water_level = -1.0f){
        for(int i = 0; i < triangles_in_a_row; i++){
            for(int j = 0; j < triangles_in_a_row; j++) {

                
                float x00 = triangles_in_a_row/2 - (int)i;
                float y00 = height_map[i + 1][j + 1];
                float z00 = (triangles_in_a_row/2 - (int)j % triangles_in_a_row);

                float x01 = x00;
                float y01 = height_map[i +1][j];
                float z01 = z00 + 1.0f;

                float x10 = x00 + 1;
                float y10 = height_map[i][j + 1];
                float z10 = z00 - 0.0f;

                float x11 = x00 + 1;
                float y11 = height_map[i][j];
                float z11 = z00 + 1.0f;

                //triangle 00 01 10
                glm::vec3 v1 = {x01 - x00, y01 - y00, z01 - z00};
                glm::vec3 v2 = {x10 - x00, y10 - y00, z10 - z00};
                glm::vec3 cross = glm::cross(v1, v2);
                Vertex3D_pos norm = {cross.x, cross.y, cross.z};
                TerrainVertex t = {x00, y00, z00, norm, 0.0f, 1.0f};
                terrainVertices.push_back(t);
                t = {x01, y01, z01, norm, 0.0f, 0.0f};
                terrainVertices.push_back(t);
                t = {x10, y10, z10, norm, 1.0f, 0.0f};
                terrainVertices.push_back(t);

                //triangle 01 11 10
                v2 = {x01 - x11, y01 - y11, z01 - z11};
                v1 = {x10 - x11, y10 - y11, z10 - z11};
                cross = glm::cross(v1, v2);
                norm = {cross.x, cross.y, cross.z};
                t = {x01, y01, z01, norm, 0.0f, 1.0f};
                terrainVertices.push_back(t);
                t = {x11, y11, z11, norm, 1.0f, 1.0f};
                terrainVertices.push_back(t);
                t = {x10, y10, z10, norm, 1.0f, 0.0f};
                terrainVertices.push_back(t);

                if(water_level + 1.0f >= y00){
                    Vertex3D_pos norm = {0.0f, 1.0f, 0.0f};
                    TerrainVertex w = {x00, water_level, z00, norm, 0.0f, 0.0f};
                    waterVertices.push_back(w);
                    w =  {x01, water_level, z01, norm, 0.0f, 0.0f};
                    waterVertices.push_back(w);
                    w =  {x10, water_level, z10, norm, 0.0f, 0.0f};

                    waterVertices.push_back(w);
                    w =  {x01, water_level, z01, norm, 0.0f, 0.0f};
                    waterVertices.push_back(w);
                    w =  {x11, water_level, z11, norm, 0.0f, 0.0f};
                    waterVertices.push_back(w);
                    w =  {x10, water_level, z10, norm, 0.0f, 0.0f};
                    waterVertices.push_back(w);
                }
            }
        }
        glGenVertexArrays(1, &tVAO);
        glGenBuffers(1, &terrainVBO);
        glBindVertexArray(tVAO);
        glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
        glBufferData(GL_ARRAY_BUFFER, terrainVertices.size() * sizeof(TerrainVertex), &terrainVertices[0], GL_STATIC_DRAW);
    
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)(sizeof(float)*3));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)(sizeof(float)*6));
        glBindVertexArray(0);

        //
        glGenVertexArrays(1, &wVAO);
        glGenBuffers(1, &waterVBO);
        glBindVertexArray(wVAO);
        glBindBuffer(GL_ARRAY_BUFFER, waterVBO);
        glBufferData(GL_ARRAY_BUFFER, waterVertices.size() * sizeof(TerrainVertex), &waterVertices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)(sizeof(float)*3));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)(sizeof(float)*6));
        glBindVertexArray(0);

        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    }

    Shader* loadShader(std::string name){
        Shader* shader = new Shader((get_shader_path() + name +".vert").c_str(), (get_shader_path() + name + ".frag").c_str());
        return shader;
    }
private:
    float skyboxVertices[36*3] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
};

#endif