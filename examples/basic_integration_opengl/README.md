# Best practices on Graphics Programming
Working on OpenGL

## Introduction
- When we create vertex shaders we better send a big chunk of data to the GPU, instead of sending small chunks of data multiple times. That's because sending data from the CPU to the GPU is expensive (slow). Once data is on the GPU, it's fast to process it. On OpenGL, we can use Vertex Buffer Objects (VBO) to send data to the GPU.
- Minimum setup for modern OPENGL is to setup a vertex and fragment shader.
- Declaring a uniform in a GLSL shader is like declaring a global variable in C. If it's not used, the compiler will optimize it out.