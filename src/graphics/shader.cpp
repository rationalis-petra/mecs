#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <string>
#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "graphics/shader.hpp"

using std::string;

const string shader_path = "resources/shaders/";

unsigned int new_shader_program(const string program_name) {
  unsigned int vertex_shader;
  unsigned int fragment_shader;
  unsigned int shader_program;

  std::ifstream vertex_shader_file;
  std::ifstream fragment_shader_file;

  string vertex_shader_path = shader_path + program_name + ".vert";
  string fragment_shader_path = shader_path + program_name + ".frag";

  try {
    vertex_shader_file.open(vertex_shader_path);
    fragment_shader_file.open(fragment_shader_path);

    int  success = 1;
    char info_log[512];

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    string vertex_file_content = string(
        std::istreambuf_iterator<char>(vertex_shader_file),
        std::istreambuf_iterator<char>());

    const char* vertex_source = vertex_file_content.c_str();
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
      // TODO: loop until infolog empty
      glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
      std::cerr << "error in new_window: failed to compile vertex shader" << std::endl;
      std::cerr << info_log;
      return 0;
    }
    vertex_shader_file.close();

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    string fragment_file_content = string(
        std::istreambuf_iterator<char>(fragment_shader_file),
        std::istreambuf_iterator<char>()).c_str();
    const char* fragment_source = fragment_file_content.c_str();
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
      glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
      std::cerr << "error in new_window: failed to compile fragment shader" << std::endl;
      std::cerr << info_log;
    }

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader_program, 512, NULL, info_log);
      perror("error in new_window: filed to link shaders\n");
      perror(info_log);
    }

    fragment_shader_file.close();

    // Cleanup
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);  

    return shader_program;
  }
  catch (std::ifstream::failure e) {
    std::cerr << "error when creating shader program: " << program_name << "file not successfully read" << std::endl;
    return 0;
  }
}

unsigned int get_uniform(unsigned int shader, string uniform_name) {
  return glGetUniformLocation(shader, uniform_name.c_str());
}
