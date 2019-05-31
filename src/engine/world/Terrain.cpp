#include "Terrain.hpp"

float** Terrain::heightMap = (float**) malloc(size*sizeof(float*));

float get_fract(float f);

Terrain::Terrain(){
    generateTerrain(Terrain::size);
    genMesh(size - 1, heightMap, waterLevel);
}

Terrain::~Terrain(){

}

void Terrain::generateTerrain(const unsigned int size){
    unsigned char* buffer = (unsigned char*) malloc(size*size);

    for(int i = 0; i < size; i++){ heightMap[i] = (float*) malloc(size*sizeof(float)); }

    std::ifstream file ("testmap4.data", std::ios::in | std::ios::binary);
    if(!file)
        ERROR("no file");
    
    if (!file.read((char*)buffer, (size * size)))
        ERROR("failed to read");
    file.close();

    for(int i = 0; i < size; i++){
        for(int j = 0 ; j < size; j++){
            heightMap[i][j] = ((float)*buffer + yoffset) * scale ;
            buffer++;
        }
    }
}
float Terrain::getHeightForPos(float x, float y){
    // return whole values
    int xmin, xmax, ymin, ymax;
    if(x == floorf(x)){
        xmin = (int)x;
        xmax = xmin;
    } else {
        xmax = (int)floorf(x);
        xmin = (int)ceilf(x);
    }

    if(y == floorf(y)){
        ymin = (int)y;
        ymax = ymin;
    } else {
        ymin = (int)floorf(y);
        //int ymax = ymin + 1;
        ymax = (int)ceilf(y);
    }

    float resymin = ((1.0f - get_fract(y)) * heightMap[512 - xmin][512 - ymin]) + (get_fract(y) * heightMap[512 - xmin][512 - ymax]);
    float resymax = ((1.0f - get_fract(y)) * heightMap[512 - xmax][512 - ymin]) + (get_fract(y) * heightMap[512 - xmax][512 - ymax]);
    
    float result_height = ((get_fract(x) * resymin) + ((1.0f - get_fract(x)) * resymax));
    //std::cout << "xpos : " << x << " ypos: " << y << "\n";
    //std::cout << xmin << " " << ymin << " " << xmax << " " << ymin << "\n" << xmax << " " << ymin << " " << xmax << " " << ymax << "\n"; 
    //std::cout << heightMap[xmin][ymin] << " " << heightMap[xmax][ymin] << "\n" << heightMap[xmax][ymin] << " " << heightMap[xmax][ymax] << "\n";

    //std::cout << "\nresult height : " << result_height << "\n";
    return result_height;
}

float get_fract(float f){
    float d = f - (long)f;
    return d;
}