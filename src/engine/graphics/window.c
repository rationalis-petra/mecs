#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/graphics.h"
#include "engine/math.h"

#ifdef DEBUG
#include <stdio.h>
#endif

GLFWwindow* window = NULL;


unsigned int VBO;
unsigned int VAO;
unsigned int shader_program;
int offset_uniform;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

int new_window(int width, int height)
{

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
#ifdef DEBUG
  if (!window) {
    fprintf(stderr, "error in new_window: failed to create GLFW window\n");
  }
#endif
  glfwMakeContextCurrent(window);

#ifdef DEBUG
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "error in new_window: failed to initialize GLAD\n");
  }
#else gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
#endif

  glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);

  glViewport(0, 0, 1280, 720);

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  // Triangle setup, will modify
  float vertices[] = {
		     -0.1f, -0.1f, 0.0f,
		      0.1f, -0.1f, 0.0f,
		      0.0f,  0.1f, 0.0f
  };
  glGenVertexArrays(1, &VAO);  
  glGenBuffers(1, &VBO);  

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);  


  shader_program = new_shader_program("basic");
  offset_uniform = glGetUniformLocation(shader_program, "offset");

  return 0;
}

void delete_window(int window) {
  glfwTerminate();
}

int window_should_close() {
  return glfwWindowShouldClose(window);
}

void display() {
  glfwSwapBuffers(window);
  glClear(GL_COLOR_BUFFER_BIT);
}

void poll_events() {
  glfwPollEvents();
}

void draw_triangle_at(Vec2i position) {
  Vec2f new_pos;
  new_pos.x = (float) position.x / 20;
  new_pos.y = (float) position.y / 20;

  glUniform3f(offset_uniform, new_pos.x, new_pos.y, 0.0f);
  glUseProgram(shader_program);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

int key_is_pressed(int key) {
  return (glfwGetKey(window, key) == GLFW_PRESS);
}
