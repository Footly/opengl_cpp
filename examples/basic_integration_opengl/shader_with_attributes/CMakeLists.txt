#Creat another main_executable
add_executable(shaders_with_attributes main_shaders_with_attributes.cpp)

#Add directories interfaces
target_include_directories(shaders_with_attributes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

#Link the GLFW library
target_link_libraries(shaders_with_attributes ${LIBS})
