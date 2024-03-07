#ifndef MESHES_H_INCLUDED
#define MESHES_H_INCLUDED

struct Mesh
{
    int vertex_count;
    int size;
    void* data;
    int type;
};

void render_mesh(struct Mesh* mesh);

#endif