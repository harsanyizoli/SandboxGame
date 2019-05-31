#include "util.h"

Paths paths = { std::filesystem::current_path() };

void* allocate_memory(size_t size){
    return malloc(size);
}

void updateFps(FPS *fps, double deltaTime){
    fps->frames++;
    double now = glfwGetTime();
    double elapsed = now - fps->last;
    //printf("%f %f \n", now, elapsed);
    if (elapsed >= 1.0){
        printf("%f \n", fps->frames/elapsed);
        fps->last = now;
        fps->frames = 0;
    }
}

std::string get_texture_path(){
    return paths.textures;
}
std::string get_model_path(){
    return paths.models;
}
std::string get_shader_path(){
    return paths.shaders;
}

unsigned int TextureFromFile(const char* file){
    std::string filename = get_texture_path() + file;
    unsigned int textureid;
    glGenTextures(1, &textureid);
    unsigned int width, height;
    std::vector<unsigned char> data;
    int error = lodepng::decode(data, width, height, filename.c_str());
    if(error){
        ERROR(lodepng_error_text(error));
    }
    glBindTexture(GL_TEXTURE_2D, textureid);
    //glTexStorage2D(GL_TEXTURE_2D, 2, GL_RGBA8, width, height);
    //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, &data[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return textureid; 
}

unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    unsigned int width, height;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        std::string filename = get_texture_path() + faces[i];
        std::vector<unsigned char> data;
        int error = lodepng::decode(data, width, height, filename.c_str());
        if(error){
            ERROR(lodepng_error_text(error));
        }
                
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                     0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]
        );
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}  

