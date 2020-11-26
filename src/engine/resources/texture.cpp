#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "engine.hpp"

#ifndef NDEBUG
#include <stdio.h>
#endif

using std::string;

const string texture_path = "resources/textures/";

Texture::Texture(string path) {
  string resource_path = texture_path + path;

  int width, height, nr_channels;
  unsigned char* data = stbi_load(resource_path.c_str(), &width, &height, &nr_channels, STBI_rgb);
#ifndef NDEBUG
  if (!data) {
    std::cerr << "error in load_texture: unable to load image from disk: " << path  << std::endl;
       
  }
#endif

  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}

Texture::~Texture() {};
