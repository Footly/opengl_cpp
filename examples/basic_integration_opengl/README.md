# Best practices on Graphics Programming
Working on OpenGL

## Introduction
- When we create vertex shaders we better send a big chunk of data to the GPU, instead of sending small chunks of data multiple times. That's because sending data from the CPU to the GPU is expensive (slow). Once data is on the GPU, it's fast to process it. On OpenGL, we can use Vertex Buffer Objects (VBO) to send data to the GPU.
- Minimum setup for modern OPENGL is to setup a vertex and fragment shader.
- Declaring a uniform in a GLSL shader is like declaring a global variable in C. If it's not used, the compiler will optimize it out.

## Textures
- Textures are images that we can apply to our 3D models. They are used to add detail to the model. These go from 0,0 to 1,1. The texture coordinates are called UV coordinates.
s, t and r are the names of the texture coordinates in OpenGL.
these coordinates match with the x, y and z coordinates of the vertices.
- We include the library stb_image.h to load images. This [library](https://github.com/nothings/stb) is a single header file that can load images in different formats.