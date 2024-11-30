#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

namespace shaders {
enum class Type { VERTEX, FRAGMENT };
class Shader {
 public:
  Shader(const char* shaderSource, Type type) {
    // Create gl shader object
    shader = glCreateShader(type == Type::VERTEX ? GL_VERTEX_SHADER
                                                 : GL_FRAGMENT_SHADER);
    // Attach the shader source code to the shader object
    glShaderSource(shader, 1, &shaderSource, NULL);
    // Compile the shader
    glCompileShader(shader);
    // Check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::"
                << (type == Type::VERTEX ? "VERTEX" : "FRAGMENT")
                << "::COMPILATION_FAILED\n"
                << infoLog << std::endl;
    }
  }

  unsigned int get() const { return shader; }

  ~Shader() { glDeleteShader(shader); }

 private:
  unsigned int shader;
};

class ShaderProgram {
 public:
  ShaderProgram(std::initializer_list<Shader> shaders) {
    program = glCreateProgram();
    for (auto& shader : shaders) {
      glAttachShader(program, shader.get());
    }
    glLinkProgram(program);
    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(program, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                << infoLog << std::endl;
    }
  }

  //Create operator() to run the program
  void operator()() const { glUseProgram(program); }

  ~ShaderProgram() { glDeleteProgram(program); }

 private:
  unsigned int program;
};
}  // namespace shaders