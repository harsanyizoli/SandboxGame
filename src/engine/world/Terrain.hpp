#include <iostream>
#include <vector>

#include "../graphics/buffer3d.hpp"

typedef struct {
    float x, y, z;
} vertex_3d;

class Terrain
{
public:

    Buffer3d* buffer;

private:

    int size = 1024;
    float* data;
    std::vector<vertex_3d> vertices;
    int* indices;

public:
    Terrain();
    ~Terrain();
private:
    void generateTerrain();
};
