#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

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

        printf(errorLog);
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
    float coords[] = {0.0,0.5,0.3,-1.0,-0.2,-0.5};
    unsigned shader = glCreateProgram();
    glAttachShader(shader, loadshader("vertexshader.shader", GL_VERTEX_SHADER));
    glAttachShader(shader, loadshader("fragmentshader.shader", GL_FRAGMENT_SHADER));
    glLinkProgram(shader);
    glUseProgram(shader);
    printf("%d",shaderStatus(shader));
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 6*floatsize, coords, GL_STATIC_DRAW);
    glVertexAttribPointer(0,2,GL_FLOAT, false, 2*floatsize, 0);
    glEnableVertexAttribArray(0);
    

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}