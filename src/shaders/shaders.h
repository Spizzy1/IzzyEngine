#ifndef SHADERS_H_INCLUDED
#define SHADERS_H_INCLUDED

struct Shader{
    unsigned ID;
    unsigned vao;
};


void loadshader(struct Shader* shader, const char* name);
int shaderStatus(unsigned int shader);

void select_shader(struct Shader* shader);

#endif