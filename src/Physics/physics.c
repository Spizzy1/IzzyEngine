#include "physics.h"

const int CHUNK_WIDTH = 10;
const int CHUNK_HEIGHT = 10;
const int CHUNK_AMOUNT = 10;
//PHYS_PTR** chunks
void physics_update(PHYS_PTR_vec* objects, struct Context* ctx, float* offset, float dt){
   for(int i = 0; i < objects->size; i++){
        PHYS_PTR object = objects->data[i];
        object->position = add(object->position, scale(object->velocity, dt));
        object->position = add(object->position, scale(object->acceleration, dt*dt/2));
        object->velocity = add(object->velocity, scale(object->acceleration, dt));
        //Unused for now
        //int chunk_x = floor((object->position.x+offset[0])/CHUNK_WIDTH);
        //int chunk_y = floor((object->position.y+offset[1])/CHUNK_HEIGHT);
        
        //int chunk = chunk_y*CHUNK_WIDTH + chunk_x;
        //if(chunk > CHUNK_AMOUNT) {break; }

        for(int i = 0; i < CHUNK_AMOUNT; i++){
             
        }

    }
}
struct PHYSVEC_vec* init_chunks(PHYS_PTR_vec* objects){

}
