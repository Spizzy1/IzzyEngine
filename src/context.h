#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include "CWE/vec.h"
#include "characters/characters.h"
#include "Collections/libraries.h"

typedef struct Character* CHARACTER;

declVec(CHARACTER);

struct Context
{
    struct CHARACTER_vec* character_vector;

};

#endif
