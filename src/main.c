#include "Collections/libraries.h"
#include "textures/textures.h"
#include "shaders/shaders.h"
#include "meshes/meshes.h"
#include "characters/characters.h"
#include <GLFW/glfw3.h>

int right = 0;
int up = 0;
int down = 0;
int left = 0;

void eventHandling(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS){
        
        switch (key)
        {
            case GLFW_KEY_W:
                up = 1;
                break;
            case GLFW_KEY_S:
                down = 1;
                break;
            case GLFW_KEY_A:
                left = 1; 
                break;
            case GLFW_KEY_D:
                right = 1;
                break;
        }
    }
    else if(action == GLFW_RELEASE){
        switch (key)
        {
            case GLFW_KEY_W:
                up = 0;
                break;
            case GLFW_KEY_S:
                down = 0;
                break;
            case GLFW_KEY_A:
                left = 0; 
                break;
            case GLFW_KEY_D:
                right = 0;
                break;
        }
    }
}


int main(int arg, char** args){

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
    const int ucx = glGetUniformLocation(shader->ID, "cx");
    const int ucz = glGetUniformLocation(shader->ID, "cz");
    const int ucd = glGetUniformLocation(shader->ID, "cd");
    const int ux = glGetUniformLocation(shader->ID, "x");
    const int uy = glGetUniformLocation(shader->ID, "y");
    const int uz = glGetUniformLocation(shader->ID, "z");
    const int urotate = glGetUniformLocation(shader->ID, "rotate");
    
    

    struct Texture* friren = load_image("Frierenfriday.png");
    printf("Finished loading textures\n");
    
    float camera_x = 0;
    float camera_z = 0;
    float direction = 0;
    float rotate = 0;
    struct Character* character = load_character(mesh, friren, shader);
    character->position[0] = 0;
    float targetFps = 60;
    float lTime = 0;
    int lSecond = 0;
    int frameCount = 0;
    int test;
    glfwSetTime(0);
    glfwSetKeyCallback(window, eventHandling);
    glEnableClientState(GL_VERTEX_ARRAY);
    while(!glfwWindowShouldClose(window)){
        while (glfwGetTime() - lTime < 1 / targetFps);
        if (glfwGetTime() - 1 >= lSecond)
        {
            lSecond++;
            frameCount = 0;
        }
        lTime += (int)((glfwGetTime() - lTime) * targetFps) / targetFps;
        frameCount++;
        glfwPollEvents();

        if(left){
            direction-= 0.01;
        }
        if(right){
            direction+= 0.01;
        }
        if(up){
            camera_z+= cos(direction)*0.03;
            camera_x+= sin(direction)*0.03;
        }
        if(down){
            camera_z-= cos(direction)*0.03;
            camera_x-= sin(direction)*0.03;
        }        
        rotate+= 0.12;
        glClear(GL_COLOR_BUFFER_BIT);
        glUniform1f(ucx, camera_x);
        glUniform1f(ucz, camera_z);
        glUniform1f(ucd, direction);
        glUniform1f(urotate, rotate);
        render_character(character,ux, uy,  uz,  urotate);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}
