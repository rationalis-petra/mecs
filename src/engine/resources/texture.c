#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifndef NDEBUG
#include <stdio.h>
#endif

const char texture_path[] = "resources/textures/";

void* load_texture(char* path, char* info) {
    int width, height, nr_channels;
    unsigned char* data = stbi_load(path, &width, &height, &nr_channels, 0);
    #ifndef NDEBUG
    if (!data) {
        fprintf(stderr, "errir in load_texture: unable to load image from disk\n");
    }
    #endif

    unsigned int* texture = malloc(sizeof(unsigned int));
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return texture;
}

void delete_texture(void* image) {
    free(image);
}
