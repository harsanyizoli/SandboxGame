#include "util.h"
#include "../include/lodepng.h"

void load_png_texture(const char *file_name) {
    unsigned int error;
    unsigned char *data;
    unsigned int width, height;
    error = lodepng_decode32_file(&data, &width, &height, file_name);
    if (error) {
        std::cout << error << " " << lodepng_error_text(error) << std::endl;
        exit(1);
    }
    //flip_image_vertical(data, width, height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    //std::cout << width << " " << height << std::endl;
    free(data); 
}
void flip_image_vertical(
    unsigned char *data, unsigned int width, unsigned int height)
{
    unsigned int size = width * height * 4;
    unsigned int stride = sizeof(char) * width * 4;
    unsigned char *new_data = (unsigned char*)malloc(sizeof(unsigned char) * size);
    for (unsigned int i = 0; i < height; i++) {
        unsigned int j = height - i - 1;
        memcpy(new_data + j * stride, data + i * stride, stride);
    }
    memcpy(data, new_data, size);
    free(new_data);
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

