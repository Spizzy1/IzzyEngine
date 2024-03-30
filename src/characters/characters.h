#ifndef CHARACTERS_H_INCLUDED
#define CHARACTERS_H_INCLUDED
#include "../Collections/base_rendering.h"

struct Character{
    void (*update_func)();
    struct Mesh mesh;
    struct Shader shader;
    struct Texture texture;
    float position[3];
    float rotation[3];

};
struct Character* load_character(char* shader_name, struct Mesh mesh, struct Texture texture);
void render_character(struct Character*, char* shader_name);
void remove_character(struct Character*);

#endif
