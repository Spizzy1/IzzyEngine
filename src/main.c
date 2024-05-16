#include "Collections/libraries.h"
#include "Physics/physics.h"
#include "textures/textures.h"
#include "shaders/shaders.h"
#include "meshes/meshes.h"
#include "characters/characters.h"
#include <stdio.h>
#include "context.h"
#include "CWE/logger.h"

int right = 0;
int up = 0;
int down = 0;
int left = 0;
const char* GRAPHICS_SOURCE = "Graphics Pipeline";
const char* WINDOW_SOURCE = "Window";

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
        cwlog(WINDOW_SOURCE, LOGGER_ERROR, "glfw failed to init");
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(win_width,win_height, name, NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if(glewInit()){
        cwlog(GRAPHICS_SOURCE, LOGGER_ERROR, "glew failed to init\n");
        return 0;
    }


    glViewport(0, 0, win_width, win_height);
    return window;
}
void enable_attribf(int location, int countf, int totalf, int index){
    cwlog("GRAPHICS PIPELINE", LOGGER_SETUP, "Assigning attribute pointer %d", location);
    glVertexAttribPointer(location, countf, GL_FLOAT, false, totalf*floatsize, (void*)(index*floatsize));
    glEnableVertexAttribArray(location);

}

void testfunc(struct Character* chr, struct Context* ctx){
    chr->physics_object->position.y += 0.01;
}
int main(int arg, char** args){

    const int width = 640; 
    const int height = 480;

    GLFWwindow* window = init(width, height, "IzzyEngine");

    // Allocates event vectors !!!!
    // NO EVENT CALLS OR APPENDS SHOULD HAPPEN BEFORE THIS FUNCTION CALL. I don't know how to get the allocations to happen at compile-time.
    // If you really wanna make stuff happen before that you're in "Editing the engine code" territory.
    struct Context* context = malloc(sizeof(struct Context));
    context->character_vector = CHARACTER_vec(0);
    
    if(!window){
        cwlog(WINDOW_SOURCE,LOGGER_ERROR, "Failed to initialize");
        return -1;
    }
    unsigned vbo = 0;
    unsigned vao = 0;

    cwlog(GRAPHICS_SOURCE,LOGGER_SETUP,"Assigning & Generating Vertex Buffer");
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    

    cwlog(GRAPHICS_SOURCE, LOGGER_SETUP, "Loading shaders...");
    struct Shader* shader = malloc(sizeof(struct Shader));
    loadshader(shader, "spriteshader.glsl");

    enable_attribf(0, 3, 6, 0);
    enable_attribf(1, 2, 6, 3);
    enable_attribf(2, 1, 6, 5);

    cwlog(GRAPHICS_SOURCE, LOGGER_SETUP, "Shaders loaded");
    
    const int utex = glGetUniformLocation(shader->ID, "tex");
    const int ucx = glGetUniformLocation(shader->ID, "cx");
    const int ucz = glGetUniformLocation(shader->ID, "cz");
    const int ucd = glGetUniformLocation(shader->ID, "cd");
    const int urotate = glGetUniformLocation(shader->ID, "rotate");
    
    struct Texture* friren = malloc(sizeof(struct Texture));
    load_image(friren, "Frierenfriday.png");
    cwlog(GRAPHICS_SOURCE, LOGGER_SETUP, "Finished loading textures");  

    struct Mesh* mesh = malloc(sizeof(struct Mesh));

    mesh->data = (float[6]){
    0, 0, 0, 0.5,0.5, 3
    };
    
    mesh->size=4*6;
    mesh->vertex_count=1;
    mesh->type = GL_POINTS;

    cwlog(GRAPHICS_SOURCE, LOGGER_WARN, "Graphics error, ignore if 0: %d", glGetError());
    struct Mesh* mesh2 = malloc(sizeof(struct Mesh));
    
    mesh2->data = (float[6]){
    1, 0, 0, 1,1, 3
    };
    
    mesh2->size=4*6;
    mesh2->vertex_count=1;
    mesh2->type = GL_POINTS;

    struct Physics_Object* charphys = malloc(sizeof(struct Physics_Object));
    struct Physics_Object* charphys2 = malloc(sizeof(struct Physics_Object));

    float camera_x = 0;
    float camera_z = 0;
    float direction = 0;
    float rotate = 0;
    struct Character* character = malloc(sizeof(struct Character));
    load_character(character, charphys,mesh, friren, shader);

    struct Character* character2 = malloc(sizeof(struct Character));
    load_character(character2, charphys2,mesh2, friren, shader);

    cwlog(GRAPHICS_SOURCE, LOGGER_WARN, "Graphics error, ignore if 0: %d", glGetError());
    character2->physics_object->position.x = 3;
    character2->physics_object->position.z = 0;
    character2->physics_object->position.y = 1;

    cwlog(GRAPHICS_SOURCE, LOGGER_WARN, "Graphics error, ignore if 0: %d", glGetError());
    character->physics_object->position.x = 1;
    character->physics_object->position.z = 0;
    character->physics_object->position.y = 1;

    character2->rotation.y = 0.12;
    character->rotation.y = 0.12;
    
    character->physics_object->acceleration.x = 0.1;
    character2->physics_object->acceleration.x = 0.0;

    character2->update_ev = &testfunc;
    CHARACTER_vec_append(context->character_vector, character);
    CHARACTER_vec_append(context->character_vector, character2);

    cwlog(GRAPHICS_SOURCE, LOGGER_WARN, "Graphics error, ignore if 0: %d", glGetError());
    const float targetFps = 60;
    float lTime = 0;
    int lSecond = 0;
    int frameCount = 0;
    int test;
    glfwSetTime(0);
    glfwSetKeyCallback(window, eventHandling);
    struct PHYS_PTR_vec* phys = PHYS_PTR_vec(0);
    PHYS_PTR_vec_append(phys, charphys);
    PHYS_PTR_vec_append(phys, charphys2);
    //glEnableClientState(GL_VERTEX_ARRAY);
    cwlog(GRAPHICS_SOURCE, LOGGER_WARN, "Graphics error, ignore if 0: %d", glGetError());
    cwlog(GRAPHICS_SOURCE, LOGGER_INFO, "OpenGL Version: %s", glGetString(GL_VERSION));
    float prevtime = glfwGetTime();
    while(!glfwWindowShouldClose(window)){
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
        character2->rotation.y -= 0.32;
        character->rotation.y += 0.12;
        rotate+= 0.12;

        while (glfwGetTime() - lTime < 1 / targetFps);
        if (glfwGetTime() - 1 >= lSecond)
        {
            lSecond++;
            frameCount = 0;
        }
        lTime += (int)((glfwGetTime() - lTime) * targetFps) / targetFps;
        frameCount++;
        
        float dt = glfwGetTime() - prevtime;
        prevtime = glfwGetTime();
        float* a = {0,0,0};
        physics_update(phys, context, a, dt);
        glClearColor(0, 0, 0, 1);        
        glClear(GL_COLOR_BUFFER_BIT);
        glUniform1f(ucx, camera_x);
        glUniform1f(ucz, camera_z);
        glUniform1f(ucd, direction);

        //This amount of ponter dereferencing could probably be optimized...
        
        for(int i = 0; i < context->character_vector->mem_size; i++){
            voidptr dataptr = context->character_vector->data[i];
            render_character(((struct Character*)(dataptr)));
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
