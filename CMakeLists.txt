cmake_minimum_required(VERSION 3.21.3)
project(izzyengine VERSION 0.0.1)

set(SOURCE_FILES
    src/textures/textures.c
    src/meshes/meshes.c
    src/shaders/shaders.c
    src/characters/characters.c
    src/Events/events.c
    src/Physics/collisions.c
    src/main.c
)
include_directories(include)

if(WIN32)
    add_subdirectory(Dependencies/glew)
    add_subdirectory(Dependencies/glfw)
endif()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})



if(WIN32)
    target_link_libraries(${PROJECT_NAME} glfw libglew_static opengl32 User32 Gdi32 Shell32 m)

endif()
if(LINUX)

    target_link_libraries(${PROJECT_NAME} glfw GLEW GL m)
  # Add GLFW and GLEW static libraries to project
endif()
