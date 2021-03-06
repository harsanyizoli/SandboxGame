#ifndef TYPES_H
#define TYPES_H

#include "../common.h"
#define INFO(msg) fprintf(stderr, "info: %s:%d: ", __FILE__, __LINE__); fprintf(stderr, "%s\n", msg);
#define ASPECT_RATIO (float)(16.0/9.0)

typedef struct Transform3D {
    glm::mat4 projection;// = glm::perspective(glm::radians(camera.zoom), ASPECT_RATIO, 0.1f, 100.0f);
    glm::mat4 view;// = camera.GetViewMatrix();
    glm::mat4 model;
} Transform3D;

typedef struct Transform2D {
    glm::mat4 perspective;
    glm::mat4 model;
} Transform2D;

typedef struct Vertex3D_pos {
    float x; 
    float y; 
    float z;
} Vertex3D_pos;

typedef struct Vertex2D_pos {
    float x;
    float y;
} Vertex2D_pos;

typedef struct TexCoord2D_pos {
    float u;
    float v;
} TexCoord2D_pos;

typedef struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
} Vertex;

typedef struct Point {
    float x;
    float y;
} Point;

#endif