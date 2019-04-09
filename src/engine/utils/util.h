#ifndef UTIL_H
#define UTIL_H
#include "../common.h"

typedef struct {
    int frames;
    double last = 0.0;
} FPS;

GLFWwindow* createContext();

void load_png_texture(const char *file_name);
void flip_image_vertical(unsigned char *data, unsigned int width, unsigned int height);

void updateFps(FPS *fps, double deltaTime);

#endif