#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>

#include "../graphics/TerrainRenderable.hpp"

class Terrain : public TerrainRenderable
{
public:

private:
    static const unsigned int size = 1024;

    static float** heightMap;
    float scale = 0.15f;
    float yoffset = -75.0f;
    float waterLevel = -1.5f;

public:
    Terrain();
    ~Terrain();

    static float getHeightForPos(float x, float y);
private:
    void generateTerrain(const unsigned int size);
};

#endif