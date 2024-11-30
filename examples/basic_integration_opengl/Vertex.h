#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class Vertex {
 public:
  enum class DrawType { STREAM, STATIC, DYNAMIC };

  // Constructor for only VBO
  Vertex(const std::vector<float>& vertices,
         DrawType drawType = DrawType::STATIC) {
    // Create Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create Vertex Buffer Object
    glGenBuffers(1, &VBO);
    // Bind the buffer to the GL_ARRAY_BUFFER target
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Copy the vertices data into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(),
                 drawType == DrawType::STATIC    ? GL_STATIC_DRAW
                 : drawType == DrawType::DYNAMIC ? GL_DYNAMIC_DRAW
                                                 : GL_STREAM_DRAW);

    // How to interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO
    glBindVertexArray(0);
  }

  // Constructor for VBO + EBO
  Vertex(const std::vector<float>& vertices,
         const std::vector<unsigned int>& indices,
         DrawType drawType = DrawType::STATIC) {
    // Create Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create Vertex Buffer Object
    glGenBuffers(1, &VBO);
    // Bind the buffer to the GL_ARRAY_BUFFER target
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Copy the vertices data into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(),
                 drawType == DrawType::STATIC    ? GL_STATIC_DRAW
                 : drawType == DrawType::DYNAMIC ? GL_DYNAMIC_DRAW
                                                 : GL_STREAM_DRAW);

    // Create Element Buffer Object
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(),
                 drawType == DrawType::STATIC    ? GL_STATIC_DRAW
                 : drawType == DrawType::DYNAMIC ? GL_DYNAMIC_DRAW
                                                 : GL_STREAM_DRAW);

    // How to interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO (the EBO stays bound to the VAO)
    glBindVertexArray(0);
  }
  ~Vertex() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
  }

  void bind() const { glBindVertexArray(VAO); }

  void unbind() const { glBindVertexArray(0); }

 private:
  unsigned int VBO;
  unsigned int VAO;
  unsigned int EBO;
};