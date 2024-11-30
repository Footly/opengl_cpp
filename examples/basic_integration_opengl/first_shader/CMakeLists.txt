#Create a main executable and link the GLFW library
add_executable(simple_first_shaders main_first_shaders.cpp)

#Add directories interfaces
target_include_directories(simple_first_shaders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

#Link the GLFW library
target_link_libraries(simple_first_shaders ${LIBS})