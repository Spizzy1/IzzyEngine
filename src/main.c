#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define true 1
#define false 0

struct Texture{
    int width;
    int height; 
    int bpp;
    unsigned ID;
};
void select_texture(struct Texture* texture, int uniform){
    if(texture){
        glActiveTexture(GL_TEXTURE0 + texture->ID);
        glBindTexture(GL_TEXTURE_2D, texture->ID);
        glUniform1i(uniform, texture->ID);
    }
    else{
        printf("Expected texture, got %d", texture); 
    }
}
struct Texture* load_image(const char* path){

    //Rember evil
    struct Texture* texture = malloc(sizeof(struct Texture));
    printf("loading image with path %d", path);
    unsigned char* bytes = stbi_load(path, &texture->width, &texture->height, &texture->bpp, 4);
    glGenTextures(1, &texture->ID);

    //Binds texture (selects it)
    glBindTexture(GL_TEXTURE_2D, texture->ID);
    printf("setting parameters for image\n");
    //Defaults to taking closest pixel to coordinate
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //Makes pixel indexing wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    printf("%d\n",glGetError());

    //Trust me.
    //Sets parameters for texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

    //Unselects it
    glBindTexture(GL_TEXTURE_2D, 0);
    if(bytes){
        stbi_image_free(bytes);
    }
    return texture;

}
int shaderStatus(unsigned int shader)
{
    int success = 0;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        int maxLength = 0;
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        char* errorLog = malloc(maxLength);
        glGetProgramInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

        printf("%d\n", errorLog);
        glDeleteProgram(shader);
        free(errorLog);
        return -1;
    }
    return 0;
}
unsigned loadshader(const char* name, unsigned type){
    FILE *fptr = fopen(name, "r");
    fseek(fptr, 0L, SEEK_END);
    int size = ftell(fptr);
    rewind(fptr);
    char* file = malloc(sizeof(char) * size);
    fread(file, 1, size, fptr);
    
    unsigned shader = glCreateShader(type);
    glShaderSource(shader, 1, (const char**)&file, NULL);
    glCompileShader(shader);
    shaderStatus(shader);
    free((char*)file);
    return shader;
}

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
    float coords[] = {
    -1.0, 1.0, 0.0,0.0,
    1,1, 1.0, 0.0
    -1.0, -1.0, 0.0, 1.0,
    1.0, -1.0, 1,1
    };
    unsigned shader = glCreateProgram();
    printf("Loading shaders...\n");
    glAttachShader(shader, loadshader("vertexshader.glsl", GL_VERTEX_SHADER));
    glAttachShader(shader, loadshader("fragmentshader.glsl", GL_FRAGMENT_SHADER));
    printf("Shaders loaded\n");
    glLinkProgram(shader);
    glUseProgram(shader);

    const int utex = glGetUniformLocation(shader, "tex");
    printf("%d\n",shaderStatus(shader));
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);

    printf("Assigning buffer\n");
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 16*floatsize, coords, GL_STATIC_DRAW);
    printf("Assigning attribute pointer 1\n");
    glVertexAttribPointer(0,2,GL_FLOAT, false, 4*floatsize, 0);
    glEnableVertexAttribArray(0);
    printf("Assigning attribute pointer 2\n");
    glVertexAttribPointer(1,2,GL_FLOAT, false, 4*floatsize, (void*)(2*floatsize));
    glEnableVertexAttribArray(1);

    struct Texture* friren = load_image("Frierenfriday.png");

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        select_texture(friren, utex);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}