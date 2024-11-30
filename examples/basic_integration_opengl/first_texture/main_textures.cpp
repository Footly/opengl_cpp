#include "Window.h"
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include <vector>

using namespace shaders;
using namespace textures;

int main(void) {
  // Initialize window
  Window window(800, 600, "OpenGL");

  const std::string pathVertexShader =
      "/workspaces/opengl_cpp/examples/basic_integration_opengl/shaders/vertex/"
      "shader_with_texture.vert";
  const std::string pathFragmentShader =
      "/workspaces/opengl_cpp/examples/basic_integration_opengl/shaders/"
      "fragment/shader_with_texture.frag";
  const std::string pathFragmentShader2Texture =
      "/workspaces/opengl_cpp/examples/basic_integration_opengl/shaders/"
      "fragment/shader_with_2mix_textures.frag";

  //Create Vertex Shader and Fragment Shader
  const Shader vertexShader(pathVertexShader, Type::VERTEX);
  const Shader fragmentShader(pathFragmentShader, Type::FRAGMENT);
  const Shader fragmentShader2Texture(pathFragmentShader2Texture,
                                      Type::FRAGMENT);

  //Create Shader Program by linking the shaders
  ShaderProgram shaderProgramWithTexture({vertexShader, fragmentShader});
  ShaderProgram shaderProgramWith2Textures(
      {vertexShader, fragmentShader2Texture});

  const std::vector<float> vertices = {
      // positions // colors // texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
  };

  const std::vector<unsigned int> indices = {
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
  };

  const std::vector<VertexAttribute> attributes = {
      VertexAttribute(0, 3, false, 8 * sizeof(float), 0),
      VertexAttribute(1, 3, false, 8 * sizeof(float), 3 * sizeof(float)),
      VertexAttribute(2, 2, false, 8 * sizeof(float), 6 * sizeof(float))};

  //Create Vertex Object
  const Vertex rectangleWithTexture(vertices, indices, attributes,
                                    Vertex::DrawType::STATIC);

  //Create Texture
  const Texture texture(
      "/workspaces/opengl_cpp/examples/basic_integration_opengl/resources/"
      "textures/container.jpg");
  const Texture texture2(
      "/workspaces/opengl_cpp/examples/basic_integration_opengl/resources/"
      "textures/awesomeface.png");

  //Set uniforms for textures
  shaderProgramWith2Textures();
  shaderProgramWith2Textures.setUniform(std::string("texture1"),
                                        std::initializer_list<int>{0});
  shaderProgramWith2Textures.setUniform(std::string("texture2"),
                                        std::initializer_list<int>{1});

  // render loop
  //Called every frame
  // -----------
  while (window) {
    // Calls the startup function for the window.
    // First function called in the loop
    window.startup();

    //Bind the texture
    texture.bind(0);
    texture2.bind(1);

    //Use the shader program
    shaderProgramWith2Textures();

    //Draw the triangle
    rectangleWithTexture.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Render here. Last function called in the loop
    window.render();
  }
  return 0;
}