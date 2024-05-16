#include "characters.h"
#include "../Collections/libraries.h"
#include "../Collections/base_rendering.h"

void load_character(struct Character* character, struct Physics_Object* physics_object, struct Mesh* mesh, struct Texture* texture, struct Shader* shader){

    character->update_ev = 0;
    character->physics_object = physics_object;
    character->shader = shader;
    character->mesh = mesh;
    character->texture = texture; 
    memset(&character->physics_object->position, 0, sizeof(struct Vec3));
    memset(&character->physics_object->velocity, 0, sizeof(struct Vec3));
    memset(&character->physics_object->acceleration, 0, sizeof(struct Vec3));
    character->rotation.x = 0;
    character->rotation.y = 0;
    character->rotation.z = 0;

}

void character_mesh_update(struct Character* character){
    ((float*)character->mesh->data)[0] = character->physics_object->position.x; 
    ((float*)character->mesh->data)[1] = character->physics_object->position.y;
    ((float*)character->mesh->data)[2] = character->physics_object->position.z;
    ((float*)character->mesh->data)[5] = character->rotation.y;


}
void render_character(struct Character* character){
    select_shader(character->shader);
    character_mesh_update(character); 
    //Doesn't do anything in practice
    select_texture(character->texture, glGetUniformLocation(character->shader->ID, "tex")); 
    render_mesh(character->mesh);

}
void remove_character(struct Character* character){
}
