#include "Terrain.hpp"
Terrain::Terrain(){
    //loadMesh();
    generateTerrain();
}

Terrain::~Terrain(){

}

void Terrain::generateTerrain(){

}
/*
#include <fstream>
#include <iostream>
#include <cmath>

void get_height_for_pos(float x, float y );
float get_fract(float f);
const unsigned int width = 1024;
const unsigned int size = width* width;

float height_map[width][width];

int main(int argc, char const *argv[]){

    unsigned char* buffer = new unsigned char[size];


    float posx = 0.25;
    float posy = 1.0f;

    std::ifstream file;
    file.open("testmap1.data", std::ios::in | std::ios::binary);
    file.read((char*)buffer, size);
    file.close();

    for(int i = 0; i < width; i++){
        for(int j = 0 ; j < width; j++){
            height_map[i][j] = (float)*buffer;
            //std::cout << height_map[i][j] << " ";
            buffer++;
        }
        //std::cout << "\n";
    }//
    for(int i = 0; i < 4; i++){
        get_height_for_pos(posx, posy);
        posx += 0.25f;
        posy += 0.25f;
    }//
    get_height_for_pos(posx, posy);
    return 0;
}

void get_height_for_pos(float x, float y ){
    // return whole values
    int xmin, xmax, ymin, ymax;
    if(x == floorf(x)){
        xmin = (int)x;
        xmax = xmin;
    } else {
        xmin = (int)floorf(x);
        xmax = (int)ceilf(x);
    }

    if(y == floorf(y)){
        ymin = (int)y;
        ymax = ymin;
    } else {
        ymin = (int)floorf(y);
        //int ymax = ymin + 1;
        ymax = (int)ceilf(y);
    }

    float resymin = ((1.0f - get_fract(y)) * height_map[xmin][ymin]) + ( get_fract(y) * height_map[xmin][ymax]);
    float resymax = ((1.0f - get_fract(y)) * height_map[xmax][ymin]) + (get_fract(y) * height_map[xmax][ymax]);
    
    float result_height = ((get_fract(x) * resymin) + ((1.0f - get_fract(x)) * resymax));
    std::cout << "xpos : " << x << " ypos: " << y << "\n";
    std::cout << xmin << " " << ymin << " " << xmax << " " << ymin << "\n" << xmax << " " << ymin << " " << xmax << " " << ymax << "\n"; 
    std::cout << height_map[xmin][ymin] << " " << height_map[xmax][ymin] << "\n" << height_map[xmax][ymin] << " " << height_map[xmax][ymax] << "\n";

    std::cout << "\nresult height : " << result_height << "\n";
}

float get_fract(float f){
    float d = f - (long)f;
    return d;
}
*/