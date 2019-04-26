#include "util.h"

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

