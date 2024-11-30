#include "Window.h"
#include "Vertex.h"
#include "Shader.h"
#include <vector>
#include <cmath>

using namespace shaders;

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSourceOrange =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

const char* fragmentShaderSourceYellow =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n\0";

const char* vertexShaderSourceConnectToFragmentShader =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"  // position has attribute position 0
    "out vec4 vertexColor;\n"  // specify a color output to the fragment shader
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos, 1.0);\n"  // we give a vec3 to vec4’s constructor
    " vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"  // output variable to dark-red
    "}\0";

const char* fragmentShaderSourceConnectToVertexShader =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec4 vertexColor;\n"  // input variable from vertex shader (same name and
                              // same type)
    "void main()\n"
    "{\n"
    " FragColor = vertexColor;\n"  // set the output variable to the dark-red color
    "}\n\0";

const char* fragmentShaderSourceChangeColorByUniform =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"  // we set this variable in the OpenGL code
    "void main()\n"
    "{\n"
    " FragColor = ourColor;\n"
    "}\n\0";

int main(void) {
  // Initialize window
  Window window(800, 600, "OpenGL");

  //Create Vertex Shader and Fragment Shader
  Shader vertexShader(vertexShaderSource, Type::VERTEX);
  Shader fragmentShader(fragmentShaderSourceOrange, Type::FRAGMENT);
  Shader fragmentShaderYellow(fragmentShaderSourceYellow, Type::FRAGMENT);
  Shader vertexShaderConnectToFragmentShader(
      vertexShaderSourceConnectToFragmentShader, Type::VERTEX);
  Shader fragmentShaderConnectToVertexShader(
      fragmentShaderSourceConnectToVertexShader, Type::FRAGMENT);
  Shader fragmentShaderChangeColorByUniform(
      fragmentShaderSourceChangeColorByUniform, Type::FRAGMENT);

  //Create Shader Program by linking the shaders
  ShaderProgram shaderProgramOrange({vertexShader, fragmentShader});
  ShaderProgram shaderProgramYellow({vertexShader, fragmentShaderYellow});
  ShaderProgram shaderProgramConnectToFragmentShader(
      {vertexShaderConnectToFragmentShader,
       fragmentShaderConnectToVertexShader});
  ShaderProgram shaderProgramChangeColorByUniform(
      {vertexShader, fragmentShaderChangeColorByUniform});

  std::vector<float> vertices = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                                 0.0f,  0.0f,  0.5f, 0.0f};

  std::vector<unsigned int> rec_indices = {0, 1, 3, 1, 2, 3};
  std::vector<float> rectangle_vertices = {
      // positions
      0.5f,  0.5f,  0.0f,  // top right
      0.5f,  -0.5f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f,  // bottom left
      -0.5f, 0.5f,  0.0f   // top left
  };

  std::vector<VertexAttribute> attributes = {
      VertexAttribute(0, 3, false, 3 * sizeof(float), 0)};

  Vertex vertexTriangle(vertices, attributes, Vertex::DrawType::STATIC);
  Vertex vertexRectangle(rectangle_vertices, rec_indices, attributes,
                         Vertex::DrawType::STATIC);

  // render loop
  //Called every frame
  // -----------
  while (window) {
    // Calls the startup function for the window.
    // First function called in the loop
    window.startup();

    //Get the current time
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(
        shaderProgramChangeColorByUniform.get(), "ourColor");
    shaderProgramChangeColorByUniform();
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    //Draw the triangle
    vertexTriangle.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //Draw the rectangle
    //vertexRectangle.bind();
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Render here. Last function called in the loop
    window.render();
  }
  return 0;
}