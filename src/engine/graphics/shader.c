#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/graphics.h"

const char shader_path[] = "resources/shaders/";

unsigned int new_shader_program(char* program_name) {
  unsigned int vertex_shader;
  unsigned int fragment_shader;
  unsigned int shader_program;

  
  size_t len = strlen(program_name);
  len += sizeof(shader_path);
  // for null character
  len += 1;

  // 3 characters .vs
  char* vertex_shader_path = malloc((len+3) * sizeof(char));

  strcpy(vertex_shader_path, shader_path);
  strcat(vertex_shader_path, program_name);
  strcat(vertex_shader_path, ".vs");

  char* fragment_shader_path = malloc((len+3) * sizeof(char));
  strcpy(fragment_shader_path, shader_path);
  strcat(fragment_shader_path, program_name);
  strcat(fragment_shader_path, ".fs");

  FILE* vertex_shader_file = fopen(vertex_shader_path, "r");
  FILE* fragment_shader_file = fopen(fragment_shader_path, "r");
  char* file_contents;

  int  success;
  char info_log[512];

  long file_len;
  if (vertex_shader_file) {
    fseek(vertex_shader_file, 0, SEEK_END);
    file_len = ftell(vertex_shader_file);
    fseek(vertex_shader_file, 0, SEEK_SET);

    // read into file
    // we add 1 so that we can have a null character '\0' at the end
    file_contents = malloc(file_len + sizeof(char));
    fread(file_contents, 1, file_len, vertex_shader_file);
    fclose(vertex_shader_file);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    file_contents[file_len] = '\0';
    const char* const_file = file_contents;
    glShaderSource(vertex_shader, 1, &const_file, NULL);
    glCompileShader(vertex_shader);
    free(file_contents);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
      glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
      fprintf(stderr, "error in new_window: failed to compile vertex shader\n");
      fprintf(stderr, info_log);
    }
  }
  else {
    fprintf(stderr, "failed to open file: %s\n", vertex_shader_path);
    return 0;
  }

  if (fragment_shader_file) {
    fseek(fragment_shader_file, 0, SEEK_END);
    file_len = ftell(fragment_shader_file);
    fseek(fragment_shader_file, 0, SEEK_SET);

    file_contents = malloc(file_len + sizeof(char));
    fread(file_contents, 1, file_len, fragment_shader_file);
    fclose(fragment_shader_file);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    file_contents[file_len] = '\0';
    const char* const_file = file_contents;
    glShaderSource(fragment_shader, 1, &const_file, NULL);
    glCompileShader(fragment_shader);
    free(file_contents);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
      glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
      fprintf(stderr, "error in new_window: failed to compile fragment shader\n");
      fprintf(stderr, info_log);
    }
  }
  else {
    fprintf(stderr, "failed to open file: %s\n", fragment_shader_path);
    return 0;
  }

  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, info_log);
    fprintf(stderr, "error in new_window: filed to link shaders\n");
    fprintf(stderr, info_log);
  }

  // Cleanup
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);  

  free(vertex_shader_path);
  free(fragment_shader_path);

  return shader_program;
}

unsigned int get_uniform(unsigned int shader, char* uniform_name) {
  return glGetUniformLocation(shader, uniform_name);
}
