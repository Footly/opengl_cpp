#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // glfw window creation
    window_ = glfwCreateWindow(width_, height_, title_, NULL, NULL);
    if (window_ == nullptr) {
      throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window_);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      throw std::runtime_error("Failed to initialize Glad");
    }

    //Set Viewport
    glViewport(0, 0, width_, height_);

    //Add callback as an arrow function to resize the window
    glfwSetFramebufferSizeCallback(
        window_, [](GLFWwindow* window, int width, int height) {
          glViewport(0, 0, width, height);
        });
  }
  ~Window() {
    // Cleanup code here
    glfwDestroyWindow(window_);
    glfwTerminate();
    // Initialization code here
    std::cout << "Destruct" << std::endl;
  }

  //Create startup function
  void startup() {
    //Process Inputs
    processInput();
    //Clear the screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  //Create render function
  void render() {
    //Swap Buffers
    swapBuffers();
    //Poll Events
    glfwPollEvents();
  }

  //Create function to check if window is open
  operator bool() const { return !glfwWindowShouldClose(window_); }

 private:
  enum class fillMode { FILL, LINE };
  int width_{800};
  int height_{600};
  const char* title_{"Window"};
  GLFWwindow* window_{nullptr};

  //Process input
  void processInput() {
    //Close the window
    if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window_, true);
    }
    //Check for the p key to toggle between fill and line mode
    if (glfwGetKey(window_, GLFW_KEY_P) == GLFW_PRESS) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
  }
  //Swap buffers
  void swapBuffers() { glfwSwapBuffers(window_); }
};