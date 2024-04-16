#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED
#include "../context.h"

struct Physics_Object{
    float position[3];
    float velocity[3];
    float acceleration[3];
    float mass; 
};

typedef struct Physics_Object* PHYS_PTR;
declVec(PHYS_PTR);

typedef struct PHYS_PTR_vec PHYSVEC;
declVec(PHYSVEC);

void physics_update(PHYS_PTR** chunks, struct PHYS_PTR_vec* objects, struct Context* ctx, float* offset, float dt);
struct PHYSVEC_vec* init_chunks(struct PHYS_PTR_vec* objects);

#endif
