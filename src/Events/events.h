#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

#include "../CWE/vec.h"
#include "../characters/characters.h"
#include "../context.h"

    typedef void (*evptr)(struct Character*, struct Context*);
    declVec(evptr);

#endif
