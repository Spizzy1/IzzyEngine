cmake_minimum_required(VERSION 3.5.0)
project(izzyengine VERSION 0.0.1)

set(SOURCE_FILES
    src/textures/textures.c
    src/meshes/meshes.c
    src/shaders/shaders.c
    src/main.c
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} glfw GLEW GL m)
