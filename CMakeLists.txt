cmake_minimum_required(VERSION 3.0.0)
project(izzyengine VERSION 0.0.1)

add_executable(izzyengine src/main.c)
target_link_libraries(izzyengine glfw GLEW GL)