cmake_minimum_required(VERSION 3.5.0)
project(izzyengine VERSION 0.0.1)

set(SOURCE_FILES
    src/textures/textures.c
    src/meshes/meshes.c
    src/shaders/shaders.c
    src/main.c
)

add_subdirectory(Dependancies/glew)
add_subdirectory(Dependancies/glfw)
include_directories(include)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} glfw libglew_static opengl32 User32 Gdi32 Shell32 m)

endif()
if(LINUX)
    target_link_libraries(${PROJECT_NAME} glfw GLEW GL m)
endif()