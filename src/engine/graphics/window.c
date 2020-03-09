#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef DEBUG
#include <stdio.h>
#endif

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

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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

    glViewport(0, 0, 1280, 720);

    glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);

    return 0;
}

void delete_window(int window) {
  glfwTerminate();
}
