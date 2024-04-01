#include "characters.h"
#include "../Collections/libraries.h"
#include "../Collections/base_rendering.h"

struct Character* load_character(struct Mesh* mesh, struct Texture* texture, struct Shader* shader){
    struct Character* character = malloc(sizeof(struct Character));
    character->shader = shader;
    character->mesh = mesh;
    character->texture = texture; 
    const float* base_position = (float[3]){0,0,0};
    mempcpy(character->position,base_position, 3);
    mempcpy(character->rotation, base_position, 3);
    return character;
}

void character_mesh_update(struct Character* character){
    ((float*)character->mesh->data)[0] = character->position[0];
    ((float*)character->mesh->data)[1] = character->position[1];
    ((float*)character->mesh->data)[2] = character->position[2];
    ((float*)character->mesh->data)[5] = character->rotation[1];


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
