#ifndef UTIL_H
#define UTIL_H
#include "glad.h"
#include <iostream>

typedef struct {
    int frames;
    double last = 0.0;
} FPS;

void load_png_texture(const char *file_name);
void flip_image_vertical(unsigned char *data, unsigned int width, unsigned int height);

#endif