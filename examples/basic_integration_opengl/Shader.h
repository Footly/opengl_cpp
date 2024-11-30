#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace shaders {
enum class Type { VERTEX, FRAGMENT };

class Shader {
 public:
  // Constructor that accepts raw shader source code
  Shader(const char* shaderSource, Type type) {
    compileShader(shaderSource, type);
  }

  // Constructor that accepts a file path to the shader source code
  Shader(const std::string& filePath, Type type) {
    std::cout << "Reading shader file: " << filePath << std::endl;
    std::ifstream shaderFile;
    std::stringstream shaderStream;

    // Ensure ifstream objects can throw exceptions:
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
      // Open file
      shaderFile.open(filePath);
      // Read file's buffer contents into streams
      shaderStream << shaderFile.rdbuf();
      // Close file handlers
      shaderFile.close();
      // Convert stream into string
      std::string shaderCode = shaderStream.str();
      compileShader(shaderCode.c_str(), type);
    } catch (std::ifstream::failure& e) {
      std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
  }

  unsigned int get() const { return shader; }

  ~Shader() { glDeleteShader(shader); }

 private:
  unsigned int shader;

  void compileShader(const char* shaderSource, Type type) {
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

  // Set uniforms. Uniforms can be float, integer, unsigned integer. Pass std string reference and initializer list
  void setUniform(const std::string& name,
                  std::initializer_list<float> values) {
    //Static assert to check if the size of the initializer list is less than 4
    if (values.size() > 4) {
      throw std::runtime_error("Number of values should be less than 4");
    }
    //Switch case to check the size of the initializer list
    switch (values.size()) {
      //If the size is 1
      case 1:
        //Set the uniform value
        glUniform1f(glGetUniformLocation(program, name.c_str()),
                    *values.begin());
        break;
      //If the size is 2
      case 2:
        //Set the uniform value
        glUniform2f(glGetUniformLocation(program, name.c_str()),
                    *values.begin(), *(values.begin() + 1));
        break;
      //If the size is 3
      case 3:
        //Set the uniform value
        glUniform3f(glGetUniformLocation(program, name.c_str()),
                    *values.begin(), *(values.begin() + 1),
                    *(values.begin() + 2));
        break;
      //If the size is 4
      case 4:
        //Set the uniform value
        glUniform4f(glGetUniformLocation(program, name.c_str()),
                    *values.begin(), *(values.begin() + 1),
                    *(values.begin() + 2), *(values.begin() + 3));
        break;
    }
  }

  void setUniform(const std::string& name, std::initializer_list<int> values) {
    if (values.size() > 4) {
      throw std::runtime_error("Number of values should be less than 4");
    }
    switch (values.size()) {
      case 1:
        glUniform1i(glGetUniformLocation(program, name.c_str()),
                    *values.begin());
        break;
      case 2:
        glUniform2i(glGetUniformLocation(program, name.c_str()),
                    *values.begin(), *(values.begin() + 1));
        break;
      case 3:
        glUniform3i(glGetUniformLocation(program, name.c_str()),
                    *values.begin(), *(values.begin() + 1),
                    *(values.begin() + 2));
        break;
      case 4:
        glUniform4i(glGetUniformLocation(program, name.c_str()),
                    *values.begin(), *(values.begin() + 1),
                    *(values.begin() + 2), *(values.begin() + 3));
        break;
    }
  }

  void setUniform(const std::string& name,
                  std::initializer_list<unsigned int> values) {
    if (values.size() > 4) {
      throw std::runtime_error("Number of values should be less than 4");
    }
    switch (values.size()) {
      case 1:
        glUniform1ui(glGetUniformLocation(program, name.c_str()),
                     *values.begin());
        break;
      case 2:
        glUniform2ui(glGetUniformLocation(program, name.c_str()),
                     *values.begin(), *(values.begin() + 1));
        break;
      case 3:
        glUniform3ui(glGetUniformLocation(program, name.c_str()),
                     *values.begin(), *(values.begin() + 1),
                     *(values.begin() + 2));
        break;
      case 4:
        glUniform4ui(glGetUniformLocation(program, name.c_str()),
                     *values.begin(), *(values.begin() + 1),
                     *(values.begin() + 2), *(values.begin() + 3));
        break;
    }
  }

  //Create operator() to run the program
  void operator()() const { glUseProgram(program); }

  ~ShaderProgram() { glDeleteProgram(program); }

 private:
  unsigned int program;
};
}  // namespace shaders