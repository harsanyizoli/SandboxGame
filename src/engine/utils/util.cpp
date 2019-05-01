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

