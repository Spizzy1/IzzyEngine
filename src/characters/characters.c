#include "characters.h"
#include "../Collections/libraries.h"
#include "../Collections/base_rendering.h"

struct Character* load_character(struct Mesh* mesh, struct Texture* texture, struct Shader* shader){
    struct Character* character = malloc(sizeof(struct Character));
    character->update_ev = 0;
    character->shader = shader;
    character->mesh = mesh;
    character->texture = texture; 
    
    character->physics_object->position.x = 0;
    character->physics_object->position.x = 0;
    character->physics_object->position.x = 0;

    character->rotation.x = 0;
    character->rotation.y = 0;
    character->rotation.z = 0;

    return character;
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
