#include "window.h"

int main() {
  try {
    auto window = core::Window(200, 522, "caca de vaca");
    while (1) {}
  } catch (const std::exception& e) {
    std::cerr << "An exception occurred: " << e.what() << std::endl;
  }

  std::cout << "End program" << std::endl;
  return 0;
}