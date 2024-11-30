#include "Window.h"
#include "Vertex.h"
#include "Shader.h"
#include <vector>
#include <cmath>

using namespace shaders;

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"  // position has attribute position 0
    "layout (location = 1) in vec3 aColor;\n"  // color has attribute position 1
    "out vec3 ourColor;\n"  // output a color to the fragment shader
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos, 1.0);\n"
    " ourColor = aColor;\n"  // set ourColor to input color from the vertex data
    "}\0";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(ourColor, 1.0);\n"
    "}\n\0";

int main(void) {
  // Initialize window
  Window window(800, 600, "OpenGL");

  //Create Vertex Shader and Fragment Shader
  const Shader vertexShader(vertexShaderSource, Type::VERTEX);
  const Shader fragmentShader(fragmentShaderSource, Type::FRAGMENT);

  //Create Shader Program by linking the shaders
  const ShaderProgram shaderProgramWithAttributes(
      {vertexShader, fragmentShader});

  const std::vector<float> vertices = {
      // positions // colors
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom left
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f};  // top

  const std::vector<VertexAttribute> attributes = {
      VertexAttribute(0, 3, false, 6 * sizeof(float), 0),
      VertexAttribute(1, 3, false, 6 * sizeof(float), 3 * sizeof(float))};

  //Create Vertex Object
  const Vertex vertexTriangle(vertices, attributes, Vertex::DrawType::STATIC);

  // render loop
  //Called every frame
  // -----------
  while (window) {
    // Calls the startup function for the window.
    // First function called in the loop
    window.startup();

    //Use the shader program
    shaderProgramWithAttributes();

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