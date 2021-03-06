#ifndef UTIL_H
#define UTIL_H
#include "../common.h"
#include <filesystem>
#include <lodepng.h>
#include <vector>
#include <algorithm>

typedef struct {
    int frames;
    double last = 0.0;
} FPS;

void* allocate_memory(size_t size);

void updateFps(FPS *fps, double deltaTime);

typedef struct {
    std::string current_dir;
    std::string textures = current_dir + "/textures/";
    std::string shaders = current_dir + "/shaders/";
    std::string models = current_dir + "/model/";
} Paths;

std::string get_texture_path();
std::string get_model_path();
std::string get_shader_path();

unsigned int TextureFromFile(const char* file);
unsigned int loadCubemap(std::vector<std::string> faces);

#endif