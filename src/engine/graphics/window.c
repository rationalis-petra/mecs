#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/graphics.h"
#include "engine/math.h"

#ifdef DEBUG
#include <stdio.h>
#endif

GLFWwindow* window = NULL;
Cursor cursor = {{{0.0d, 0.0d}}};
float aspect;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    aspect = (float) width / height;
}  

int new_window(int width, int height)
{

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(1280, 720, "LearnOpenGL", NULL, NULL);
  aspect = (float) 1280 / 720;
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
#else
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
#endif

  glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);

  glViewport(0, 0, 1280, 720);

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  glEnable(GL_DEPTH_TEST);

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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void poll_events() {
  glfwPollEvents();
}


int key_is_pressed(int key) {
  return (glfwGetKey(window, key) == GLFW_PRESS);
}

Cursor get_cursor_pos() {
  glfwGetCursorPos(window, &cursor.x, &cursor.y);
  return cursor;
}

float get_window_aspect() {
  return aspect;
}
