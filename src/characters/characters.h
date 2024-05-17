#ifndef CHARACTERS_H_INCLUDED
#define CHARACTERS_H_INCLUDED

#include "../Collections/libraries.h"
#include "../Collections/base_rendering.h"
#include "../Events/events.h"
#include "../context.h"
#include "../Physics/physics.h"

struct Character;

typedef void (*evptr)(struct Character*, struct Context*);

struct Character{
    evptr update_ev;
    struct Mesh* mesh;
    struct Shader* shader;
    struct Texture* texture;
    struct Physics_Object* physics_object;
    struct Vec3 rotation;
}; 


void render_character(struct Character* character);
void load_character(struct Character* character, struct Physics_Object* physics_object, struct Mesh* mesh, struct Texture* texture, struct Shader* shader);
void remove_character(struct Character*);

#endif
