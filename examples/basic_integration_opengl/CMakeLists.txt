cmake_minimum_required(VERSION 3.12)
project(basic_integration_opengl)

#Fecth the GLFW library using fetchContent
include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)

FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    FetchContent_Populate(glad)
    set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
    set(GLAD_API "gl=" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
    set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
    add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
endif()
# Add stb_image library using ExternalProject
include(ExternalProject)

ExternalProject_Add(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    SOURCE_DIR ${CMAKE_BINARY_DIR}/stb-src
    BINARY_DIR ${CMAKE_BINARY_DIR}/stb-build
)

add_library(stb_image INTERFACE)
add_dependencies(stb_image stb)
target_include_directories(stb_image INTERFACE ${CMAKE_BINARY_DIR}/stb-src)
target_compile_definitions(stb_image INTERFACE STB_IMAGE_IMPLEMENTATION)

#set libraries dependencies
set(LIBS glfw glad stb_image)

#add subdirectories for each executable
add_subdirectory(first_shader)
add_subdirectory(shader_with_attributes)
add_subdirectory(first_texture)