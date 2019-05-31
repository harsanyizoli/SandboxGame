#ifndef UI_H
#define UI_H

#include "types.h"
#include "../utils/util.h"
#include "shader.h"

#include <vector>

class ui
{
private:
    Shader* shader2d = nullptr;

    float width, height;
    Point center;

    unsigned int crosshairTextureId;
    const char* crosshairTextureName = "crosshair2.png";
    const float crosshairSize = 48.0f;
    unsigned int crosshairVertCount = 0;
    
    unsigned int minimapTextureId;
    const char* minimapTextureName = "minimap.png";
    float minimapSize;
    unsigned int minimapVertCount = 0;

    Transform2D trans;

    unsigned int VAO, VBO;
    std::vector<glm::vec4> vertices;
    
public:
    ui(float w, float h) 
        : width(w), height(h) {
        center = {width / 2, height / 2};
        crosshairTextureId = TextureFromFile(crosshairTextureName);
        minimapTextureId = TextureFromFile(minimapTextureName);
        shader2d = new Shader((get_shader_path() + "ui.vert").c_str(), (get_shader_path() + "ui.frag").c_str());
        trans.model = glm::mat4(1.0f);
        trans.perspective = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
        minimapSize = width / 6.0f;
        makeCrosshair();
        makeMinimap();
        setupVAO();
    }
    ~ui() {}

    void DrawUI(){
        glDisable(GL_DEPTH_TEST);
        shader2d->use();
        shader2d->setMat4("projection", trans.perspective);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glBindVertexArray(VAO);
        shader2d->setInt("ch", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, crosshairTextureId);
        glDrawArrays(GL_TRIANGLES, 0, crosshairVertCount);
        shader2d->setInt("ch", 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, minimapTextureId);
        glDrawArrays(GL_TRIANGLES, crosshairVertCount, minimapVertCount);
        
        glBindVertexArray(0);
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
    }
private:
    void makeCrosshair(){
        glm::vec4 tl = {center.x - crosshairSize /2, center.y - crosshairSize / 2, 1.0f, 0.0f};
        glm::vec4 bl = {tl.x, tl.y + crosshairSize, 0.0f, 0.0f};
        glm::vec4 br = {bl.x + crosshairSize, bl.y, 0.0f, 1.0f};
        glm::vec4 tr = {br.x, br.y - crosshairSize, 1.0f, 1.0f};
        
        vertices.push_back(tl);
        vertices.push_back(bl);
        vertices.push_back(tr);

        vertices.push_back(tr);
        vertices.push_back(bl);
        vertices.push_back(br);
        crosshairVertCount = vertices.size();
        shader2d->use();
        shader2d->setInt("ch", 0);
    }

    void makeMinimap(){
        glm::vec4 bl = {50.0f, height - 50.0f, 0.0f, 1.0f};
        glm::vec4 br = {bl.x + minimapSize, bl.y, 1.0f, 1.0f};
        glm::vec4 tr = {br.x, br.y - minimapSize, 1.0f, 0.0f};
        glm::vec4 tl = {tr.x - minimapSize, tr.y, 0.0f, 0.0f};

        vertices.push_back(tl);
        vertices.push_back(bl);
        vertices.push_back(tr);

        vertices.push_back(tr);
        vertices.push_back(bl);
        vertices.push_back(br);
        minimapVertCount = vertices.size() - crosshairVertCount;
    }

    void setupVAO(){
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), &vertices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
        glBindVertexArray(0);
    }
};

#endif