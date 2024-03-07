#include "../libraries.h"
#include "meshes.h"

void render_mesh(struct Mesh* mesh){
    glBufferData(GL_ARRAY_BUFFER, mesh->size, mesh->data, GL_STATIC_DRAW);
    glDrawArrays(mesh->type, 0, mesh->vertex_count);
}
