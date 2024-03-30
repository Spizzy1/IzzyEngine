#ifndef CHARACTERS_H_INCLUDED
#define CHARACTERS_H_INCLUDED
#include "../Collections/base_rendering.h"

struct Character{
    void (*update_func)();
    struct Mesh* mesh;
    struct Shader* shader;
    struct Texture* texture;
    float position[3];
    float rotation[3];
};
void render_character(struct Character* character, int ux, int uy, int uz, int urotation);
struct Character* load_character(struct Mesh* mesh, struct Texture* texture, struct Shader* shader);
void remove_character(struct Character*);

#endif
