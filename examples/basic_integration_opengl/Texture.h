#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace textures {
class Texture {
 public:
  Texture(const std::string& path) : path_(path) {
    // Load the texture
    loadTexture();
  }

  ~Texture() { glDeleteTextures(1, &texture_); }

  void bind(unsigned char textureUnit = 0) const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, texture_);
  }

  void unbind(unsigned char textureUnit = 0) const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

 private:
  std::string path_;
  unsigned int texture_;

  void loadTexture() {
    // Determine the format based on the file extension
    const GLenum format =
        (path_.substr(path_.find_last_of(".") + 1) == "png") ? GL_RGBA : GL_RGB;

    // Flip the texture
    stbi_set_flip_vertically_on_load(true);
    // Load the texture
    int width, height, nrChannels;
    unsigned char* data =
        stbi_load(path_.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
      glGenTextures(1, &texture_);
      glBindTexture(GL_TEXTURE_2D, texture_);
      // Set the texture wrapping/filtering options (on the currently bound texture object)
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      // Generate the texture
      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                   GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    } else {
      std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
  }
};
}  // namespace textures