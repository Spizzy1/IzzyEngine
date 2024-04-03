#include "Collections/libraries.h"
#include "textures/textures.h"
#include "shaders/shaders.h"
#include "meshes/meshes.h"
#include "characters/characters.h"
#include <GLFW/glfw3.h>
#include "events/events.h"
#include "context.h"
#define floatsize sizeof(float)


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

GLFWwindow* init(const int win_width, const int win_height, const char* name){
    if(!glfwInit()){
        printf("glfw failed to init\n");
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_FOCUSED, true);
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(win_width,win_height, name, NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if(glewInit()){
        printf("glew failed to init\n");
        return 0;
    }


    glViewport(0, 0, win_width, win_height);
    return window;
}
void enable_attribf(int location, int countf, int totalf, int index){
    printf("Assigning attribute pointer %d\n", location);
    glVertexAttribPointer(location, countf, GL_FLOAT, false, totalf*floatsize, (void*)(index*floatsize));
    glEnableVertexAttribArray(location);

}

void testfunc(struct Character* chr, struct Context* ctx){
    chr->position[1] += 0.01;
}
int main(int arg, char** args){


    const int width = 640; 
    const int height = 480;

    GLFWwindow* window = init(width, height, "IzzyEngine");

    // Allocates event vectors !!!!
    // NO EVENT CALLS OR APPENDS SHOULD HAPPEN BEFORE THIS FUNCTION CALL. I don't know how to get the allocations to happen at compile-time.
    // If you really wanna make stuff happen before that you're in "Editing the engine code" territory.
    struct Context* context = malloc(sizeof(struct Context));
    context->character_vector = CHARACTER_vec(8);
    
    if(!window){
        printf("Failed to initialize\n");
        return -1;
    }
    unsigned vbo = 0;
    unsigned vao = 0;

    printf("Assigning & Generating Vertex Buffer\n");
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    

    printf("Loading shaders...\n");
    struct Shader* shader = loadshader("spriteshader.glsl");

    enable_attribf(0, 3, 6, 0);
    enable_attribf(1, 2, 6, 3);
    enable_attribf(2, 1, 6, 5);

    printf("Shaders loaded\n");
    
    const int utex = glGetUniformLocation(shader->ID, "tex");
    const int ucx = glGetUniformLocation(shader->ID, "cx");
    const int ucz = glGetUniformLocation(shader->ID, "cz");
    const int ucd = glGetUniformLocation(shader->ID, "cd");
    const int urotate = glGetUniformLocation(shader->ID, "rotate");
    
    

    struct Texture* friren = load_image("Frierenfriday.png");
    printf("Finished loading textures\n");  

    struct Mesh* mesh = malloc(sizeof(struct Mesh));

    mesh->data = (float[6]){
    0, 0, 0, 0.5,0.5, 3
    };
    
    mesh->size=4*6;
    mesh->vertex_count=1;
    mesh->type = GL_POINTS;

    struct Mesh* mesh2 = malloc(sizeof(struct Mesh));
    
    mesh2->data = (float[6]){
    1, 0, 0, 1,1, 3
    };
    
    mesh2->size=4*6;
    mesh2->vertex_count=1;
    mesh2->type = GL_POINTS;

    float camera_x = 0;
    float camera_z = 0;
    float direction = 0;
    float rotate = 0;
    struct Character* character = load_character(mesh, friren, shader);
    struct Character* character2 = load_character(mesh2, friren, shader);
    character2->position[0] = 3;
    character2->position[1] = 0;
    character2->position[2] = 1;

    character->position[0] = 1;
    character->position[1] = 0;
    character->position[2] = 1;

    character2->rotation[1] = 0.12;
    character->rotation[1] = 0.12;

    character2->update_ev = &testfunc;

    context->character_vector->data[0] = character2;
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
           direction-= 0.03;
        }
        if(right){
            direction+= 0.03;
        }
        if(up){
            camera_z+= cos(direction)*0.03;
            camera_x+= sin(direction)*0.03;
        }
        if(down){
            camera_z-= cos(direction)*0.03;
            camera_x-= sin(direction)*0.03;
        }        
        character2->rotation[1] -= 0.32;
        character->rotation[1] += 0.12;
        rotate+= 0.12;
        glClear(GL_COLOR_BUFFER_BIT); 
        glUniform1f(ucx, camera_x);
        glUniform1f(ucz, camera_z);
        glUniform1f(ucd, direction);
        render_character(character);
        render_character(character2);

        //This amount of ponter dereferencing could probably be optimized...
        
        for(int i = 0; i < context->character_vector->mem_size; i++){
            voidptr dataptr = context->character_vector->data[i];
            if(dataptr){
                if(((struct Character*)(dataptr))->update_ev){
                    (((struct Character*)(dataptr))->update_ev)(((struct Character*)(dataptr)), context);
                }
            }
        }
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}
