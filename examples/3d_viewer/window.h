#ifndef __WINDOW_H_
#define __WINDOW_H_
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <memory>

namespace core {
class Window {
 public:
  Window(int width, int height, const char* const title)
      : width_(width), height_(height), title_(title) {
    // Initialization code here
    std::cout << "Initialized" << std::endl;
    // Initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfw window creation
    window_ = glfwCreateWindow(width_, height_, title_, NULL, NULL);
    if (window_ == nullptr) {
      throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window_);

    // Initialize Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      throw std::runtime_error("Failed to initialize Glad");
    }
  }
  ~Window() {
    // Cleanup code here
    glfwDestroyWindow(window_);
    glfwTerminate();
    // Initialization code here
    std::cout << "Destruct" << std::endl;
  }

 private:
  int width_{800};
  int height_{600};
  const char* title_{"Window"};
  GLFWwindow* window_{nullptr};
};
}  // namespace core

#endif