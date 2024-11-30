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

#set libraries dependencies
set(LIBS glfw glad)


#Create a main executable and link the GLFW library
add_executable(simple_first_shaders main_first_shaders.cpp)

#Add directories interfaces
target_include_directories(simple_first_shaders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#Link the GLFW library
target_link_libraries(simple_first_shaders ${LIBS})

#Creat another main_executable
add_executable(shaders_with_attributes main_shaders_with_attributes.cpp)

#Add directories interfaces
target_include_directories(shaders_with_attributes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#Link the GLFW library
target_link_libraries(shaders_with_attributes ${LIBS})
