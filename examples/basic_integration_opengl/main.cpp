#include "Window.h"
#include "Vertex.h"
#include "Shader.h"
#include <vector>
using namespace shaders;

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main(void) {
  // Initialize window
  Window window(800, 600, "OpenGL");

  //Create Vertex Shader
  Shader vertexShader(vertexShaderSource, Type::VERTEX);
  Shader fragmentShader(fragmentShaderSource, Type::FRAGMENT);

  //Create Shader Program
  ShaderProgram shaderProgram({vertexShader, fragmentShader});

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

  Vertex vertexTriangle(vertices, Vertex::DrawType::STATIC);
  Vertex vertexRectangle(rectangle_vertices, rec_indices,
                         Vertex::DrawType::STATIC);

  // render loop
  //Called every frame
  // -----------
  while (window) {
    // Calls the startup function for the window.
    // First function called in the loop
    window.startup();

    //Call the shader program
    shaderProgram();

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