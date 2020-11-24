#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifndef NDEBUG
#include <stdio.h>
#endif

const char texture_path[] = "resources/textures/";

void* load_texture(const char* path) {
  char* resource_path = (char*) calloc(strlen(texture_path) + strlen(path) + 1, sizeof(char));
    strcat(resource_path, texture_path);
    strcat(resource_path, path);

    int width, height, nr_channels;
    unsigned char* data = stbi_load(resource_path, &width, &height, &nr_channels, STBI_rgb);
    #ifndef NDEBUG
    if (!data) {
        perror( "error in load_texture: unable to load image from disk\n");
    }
    #endif
    free(resource_path);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned int* texture = (unsigned int*) malloc(sizeof(unsigned int));
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