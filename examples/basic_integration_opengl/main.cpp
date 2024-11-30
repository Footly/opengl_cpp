#include "window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(void) {
  // Initialize window
  Window window(1500, 600, "OpenGL");

  // render loop
  // -----------
  while (window) {
    window.startup();
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    window.cleanup();
  }
  return 0;
}

//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//  // make sure the viewport matches the new window dimensions; note that width and
//  // height will be significantly larger than specified on retina displays.
//  glViewport(0, 0, width, height);
//}