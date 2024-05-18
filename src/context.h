#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

struct Context; 

#include <CWE/vec.h>
#include "characters/characters.h"
#include "Collections/libraries.h"

typedef struct Character* CHARACTER;

declVec(CHARACTER, CHARACTER_vec);

struct Context
{
    CHARACTER_vec* character_vector;

};

#endif
