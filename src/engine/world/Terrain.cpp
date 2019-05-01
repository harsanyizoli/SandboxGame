#include "Terrain.hpp"

Terrain::Terrain(){
    std::cout << "[] Terrain generated "<< this << std::endl;
    generateTerrain();
    buffer = new Buffer3d((float*)&vertices[0], (int)vertices.size());
}

Terrain::~Terrain()
{
}
void Terrain::generateTerrain(){
    vertices.push_back({0.0f, 0.0f, 0.0f});
    vertices.push_back({0.0f, 0.0f, 1.0f});
    vertices.push_back({1.0f, 0.0f, 0.0f});

    vertices.push_back({0.0f, 0.0f, 1.0f});
    vertices.push_back({1.0f, 0.0f, 0.0f});
    vertices.push_back({1.0f, 0.0f, 1.0f});

    vertices.push_back({0.0f, 0.0f, 2.0f});
    vertices.push_back({1.0f, 0.0f, 2.0f});
    vertices.push_back({1.0f, 0.0f, 1.0f});

    vertices.push_back({0.0f, 0.0f, 2.0f});
    vertices.push_back({0.0f, 0.0f, 1.0f});
    vertices.push_back({1.0f, 0.0f, 1.0f});
    
    //
    
    vertices.push_back({1.0f, 0.0f, 0.0f});
    vertices.push_back({1.0f, 0.0f, 1.0f});
    vertices.push_back({2.0f, 0.0f, 0.0f});

    vertices.push_back({1.0f, 0.0f, 1.0f});
    vertices.push_back({2.0f, 0.0f, 0.0f});
    vertices.push_back({2.0f, 0.0f, 1.0f});

    vertices.push_back({1.0f, 0.0f, 2.0f});
    vertices.push_back({2.0f, 0.0f, 2.0f});
    vertices.push_back({2.0f, 0.0f, 1.0f});

    vertices.push_back({1.0f, 0.0f, 2.0f});
    vertices.push_back({1.0f, 0.0f, 1.0f});
    vertices.push_back({2.0f, 0.0f, 1.0f});
}