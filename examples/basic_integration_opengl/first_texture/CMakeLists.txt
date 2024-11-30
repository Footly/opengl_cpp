#Create a main executable and link the GLFW library
add_executable(first_texture main_textures.cpp)

#Add directories interfaces
target_include_directories(first_texture PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

#Link the GLFW library
target_link_libraries(first_texture ${LIBS})