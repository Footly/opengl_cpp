#include "window.h"

int main(void) {
  // Initialize window
  Window window(1500, 600, "OpenGL");

  // render loop
  //Called every frame
  // -----------
  while (window) {
    // Calls the startup function for the window.
    // First function called in the loop
    window.startup();

    // Render here. Last function called in the loop
    window.render();
  }
  return 0;
}