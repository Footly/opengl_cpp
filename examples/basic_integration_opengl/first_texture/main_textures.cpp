#include "Window.h"
#include "Vertex.h"
#include "Shader.h"
#include <vector>
#include <cmath>

using namespace shaders;

int main(void) {
  // Initialize window
  Window window(800, 600, "OpenGL");

  const std::string pathVertexShader =
      "/workspaces/opengl_cpp/examples/basic_integration_opengl/shaders/vertex/"
      "simple_vertex_shader_with_colors.vert";
  const std::string pathFragmentShader =
      "/workspaces/opengl_cpp/examples/basic_integration_opengl/shaders/"
      "fragment/simple_fragment_shader.frag";

  //Create Vertex Shader and Fragment Shader
  const Shader vertexShader(pathVertexShader, Type::VERTEX);
  const Shader fragmentShader(pathFragmentShader, Type::FRAGMENT);

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