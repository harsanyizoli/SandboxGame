#ifndef UTIL_H
#define UTIL_H
#include "glad.h"
#include <iostream>

void load_png_texture(const char *file_name);
void flip_image_vertical(unsigned char *data, unsigned int width, unsigned int height);
#endif