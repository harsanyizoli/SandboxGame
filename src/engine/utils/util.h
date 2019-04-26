#ifndef UTIL_H
#define UTIL_H
#include "../common.h"

typedef struct {
    int frames;
    double last = 0.0;
} FPS;

void* allocate_memory(size_t size);

void updateFps(FPS *fps, double deltaTime);

#endif