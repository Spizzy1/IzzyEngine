#include "../libraries.h"
#include "shaders.h"

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

        printf("%s\n", errorLog);
        glDeleteProgram(shader);
        free(errorLog);
        return -1;
    }
    return 0;
}
struct Shader* loadshader(const char* name){

    struct Shader* shader = malloc(sizeof(struct Shader));
    shader->ID = glCreateProgram();
    unsigned shaderIDs[3];
    int shader_count = 0;

    printf("\n--- LOADING IN SHADER %s ---\n", name);
    FILE *fptr = fopen(name, "r");
    fseek(fptr, 0L, SEEK_END);
    int size = ftell(fptr);
    rewind(fptr);
    char* file = malloc(sizeof(char) * size);
    fread(file, 1, size, fptr);
    printf("Last char: %d", file[size-1]);
    int begin = 0;
    int shader_type=0;
    int new_shader_type=0;
    int load = false;
    int reading = false;
    printf("Parsing shader file\n");
    for(int i = 0; i < size; i++){
        if(file[i] == '\n' && size - i > 9){
            char str[10];
            memcpy(str, file+i, 10);
            if(!strcmp("\n--VERT--\n", str)){
                new_shader_type = GL_VERTEX_SHADER;
                printf("Compiling vertex shader\n");
                load = true;
            }
            else if(!strcmp("\n--FRAG--\n", str)){
                new_shader_type = GL_FRAGMENT_SHADER;
                printf("Compiling fragment shader\n");

                load = true;
            }
            else if(!strcmp("\n--GMTR--\n", str)){
                new_shader_type = GL_GEOMETRY_SHADER;
                printf("Compiling geometry shader\n");

                load = true;
            }
        }
        if((load || i == size-1)){
            if(reading){
                printf("%x\n", shader_type);
                i+= i==size-1;
                printf("Reading Subfile\n");
                char* subfile = malloc(i-begin+1);
                subfile[i-begin] = '\0';
                printf("Copying into subfile\n");
                strncpy(subfile, file+begin,i-begin);
                printf("Creating shader object\n");
                unsigned ID = glCreateShader(shader_type);

                printf("Parsing shader source\n");
                glShaderSource(ID, 1, (const char**)&subfile, NULL);

                printf("Compiling shader\n");
                glCompileShader(ID);

                printf("Attatching shader\n");
                glAttachShader(shader->ID, ID);

                free(subfile);
                shaderIDs[shader_count] = ID;
                shader_count+=1;

            }
            shader_type = new_shader_type;
            i += 10;
            begin = i;
            reading = true;
            load = false;
            
        }
    }
    
    free((char*)file);

    glLinkProgram(shader->ID);
    printf("%d\n",shaderStatus(shader->ID));
    for(int i = 0; i < shader_count; i++){

        printf("Cleaning up shader compilation... \n");
        glDetachShader(shader->ID, shaderIDs[i]);
        glDeleteShader(shaderIDs[i]);
    }
    
    glGenVertexArrays(1, &shader->vao);
    glBindVertexArray(shader->vao);
    return shader;
}

void select_shader(struct Shader* shader){
    glUseProgram(shader->ID);
    glBindVertexArray(shader->vao);
}