#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <vector>

#include "../graphics/TerrainRenderable.hpp"

class Terrain : public TerrainRenderable
{
public:

private:
    const int size = 1024;

public:
    Terrain();
    ~Terrain();
    
private:
    void generateTerrain();
};

#endif