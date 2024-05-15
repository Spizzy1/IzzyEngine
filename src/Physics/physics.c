#include "physics.h"
#include <math.h>

const int CHUNK_WIDTH = 10;
const int CHUNK_HEIGHT = 10;
const int CHUNK_AMOUNT = 10;
void physics_update(PHYS_PTR** chunks, struct PHYS_PTR_vec* objects, struct Context* ctx, float* offset, float dt){
    for(int i = 0; i < objects->size; i++){
        PHYS_PTR object = objects->data[i];
        int chunk_x = floor((object->position[0]+offset[0])/CHUNK_WIDTH);
        int chunk_y = floor((object->position[1]+offset[1])/CHUNK_HEIGHT);
        
        int chunk = chunk_y*CHUNK_WIDTH + chunk_x;
        if(chunk > CHUNK_AMOUNT) {break; }

        for(int i = 0; i < CHUNK_AMOUNT; i++){
             
        }
        

    }
}
struct PHYSVEC_vec* init_chunks(struct PHYS_PTR_vec* objects){

}
