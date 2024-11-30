#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

struct VertexAttribute {
  unsigned int index{0};
  int size{0};
  bool normalized{false};
  int stride{0};
  int offset{0};

  VertexAttribute(int index, int size, bool normalized, int stride, int offset)
      : index(index),
        size(size),
        normalized(normalized),
        stride(stride),
        offset(offset) {}
};

class Vertex {
 public:
  enum class DrawType { STREAM, STATIC, DYNAMIC };

  // Constructor for only VBO with attributes
  Vertex(const std::vector<float>& vertices,
         const std::vector<VertexAttribute>& attributes,
         DrawType drawType = DrawType::STATIC) {
    initialize(vertices, drawType, attributes);
  }

  // Constructor for VBO + EBO with attributes
  Vertex(const std::vector<float>& vertices,
         const std::vector<unsigned int>& indices,
         const std::vector<VertexAttribute>& attributes,
         DrawType drawType = DrawType::STATIC) {
    initialize(vertices, indices, drawType, attributes);
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

  void initialize(const std::vector<float>& vertices, DrawType drawType,
                  const std::vector<VertexAttribute>& attributes) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(),
                 drawType == DrawType::STATIC    ? GL_STATIC_DRAW
                 : drawType == DrawType::DYNAMIC ? GL_DYNAMIC_DRAW
                                                 : GL_STREAM_DRAW);

    setupAttributes(attributes);

    glBindVertexArray(0);
  }

  void initialize(const std::vector<float>& vertices,
                  const std::vector<unsigned int>& indices, DrawType drawType,
                  const std::vector<VertexAttribute>& attributes) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(),
                 drawType == DrawType::STATIC    ? GL_STATIC_DRAW
                 : drawType == DrawType::DYNAMIC ? GL_DYNAMIC_DRAW
                                                 : GL_STREAM_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(),
                 drawType == DrawType::STATIC    ? GL_STATIC_DRAW
                 : drawType == DrawType::DYNAMIC ? GL_DYNAMIC_DRAW
                                                 : GL_STREAM_DRAW);

    setupAttributes(attributes);

    glBindVertexArray(0);
  }

  void setupAttributes(const std::vector<VertexAttribute>& attributes) {
    for (const auto& attr : attributes) {
      glVertexAttribPointer(attr.index, attr.size, GL_FLOAT, attr.normalized,
                            attr.stride, (void*)(intptr_t)attr.offset);
      glEnableVertexAttribArray(attr.index);
    }
  }
};