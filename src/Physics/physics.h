#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED
#include "../CWE/cwmath.h"
#include "../context.h"

struct Physics_Object{
    struct Vec3 position;
    struct Vec3 velocity;
    struct Vec3 acceleration;
    float mass; 
};


typedef struct Physics_Object* PHYS_PTR;
declVec(PHYS_PTR);

typedef struct PHYS_PTR_vec PHYSVEC;
declVec(PHYSVEC);

void physics_update(struct PHYS_PTR_vec* objects, struct Context* ctx, float* offset, float dt);
struct PHYSVEC_vec* init_chunks(struct PHYS_PTR_vec* objects);

#endif
