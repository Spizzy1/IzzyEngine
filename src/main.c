#include "libraries.h"
#include "textures/textures.h"
#include "shaders/shaders.h"
#include "meshes/meshes.h"

int main(int, char**){
    

    const int width = 640; 
    const int height = 480;
    const int floatsize = sizeof(float);

    GLFWwindow* window;
    if(!glfwInit()){
        printf("glfw failed to init\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_FOCUSED, true);
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(width,height, "IzzyEngine", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if(glewInit()){
        printf("glew failed to init\n");
        return -1;
    }


    glViewport(0, 0, width, height);
    unsigned vbo = 0;
    unsigned vao = 0;
    struct Mesh* mesh = malloc(sizeof(struct Mesh));

    mesh->data = (float[16]){
    -1.0, 1.0, 0.0,0.0,
    1,1, 1.0, 0.0,
    -1.0, -1.0, 0.0, 1.0,
    1.0, -1.0, 1,1
    };
    
    mesh->size=16*4;
    mesh->vertex_count=4;
    mesh->type = GL_TRIANGLE_STRIP;

    printf("Assigning & Generating Vertex Buffer\n");
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    printf("Loading shaders...\n");
    struct Shader* shader = loadshader("spriteshader.glsl");
    printf("Assigning attribute pointer 1\n");
    glVertexAttribPointer(0,2,GL_FLOAT, false, 4*floatsize, 0);
    glEnableVertexAttribArray(0);
    printf("Assigning attribute pointer 2\n");
    glVertexAttribPointer(1,2,GL_FLOAT, false, 4*floatsize, (void*)(2*floatsize));
    glEnableVertexAttribArray(1);

    printf("Shaders loaded\n");
    
    const int utex = glGetUniformLocation(shader->ID, "tex");
    
    

    struct Texture* friren = load_image("Frierenfriday.png");
    printf("Finished loading textures\n");
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        select_shader(shader);
        select_texture(friren, utex);
        render_mesh(mesh);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}