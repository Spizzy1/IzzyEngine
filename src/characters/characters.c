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

void render_character(struct Character* character, int ux, int uy, int uz, int urotation){
    select_shader(character->shader);
    glUniform1f(ux, character->position[0]);
    glUniform1f(uy, character->position[1]);
    //Doesn't do anything in practice
    glUniform1f(uz, character->position[2]);
    glUniform1f(urotation, character->rotation[1]);
    select_texture(character->texture, glGetUniformLocation(character->shader->ID, "tex")); 
    render_mesh(character->mesh);

}
void remove_character(struct Character* character){

}
