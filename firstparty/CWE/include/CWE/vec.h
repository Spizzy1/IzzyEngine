#ifndef CWE_VEC_H_INCLUDED
#define CWE_VEC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

//Credits to Theelf111
#if defined(_MSC_VER)
#define __auto_type auto
#endif

struct _Vector
{
    void* data;
    size_t size;
    size_t mem_size;
};

#define declVec(type, name) \
typedef struct \
{ \
    type* data; \
    size_t size; \
    size_t mem_size; \
} name

#define free_vec(vec) { free(vec->data);free(vec); }

static inline void* _new_vec(size_t size_elem, size_t size_i)
{
    struct _Vector* vec = malloc(sizeof(struct _Vector));
    vec->data = malloc(sizeof(struct _Vector) + size_elem * size_i);
    vec->size = size_i;
    vec->mem_size = size_i;
    return vec;
}

#define new_vec(type, size) _new_vec(sizeof(type), size)

static inline void _vec_mem_resize(struct _Vector* vec, size_t size_elem, size_t size_new)
{
    void* data_new = malloc(size_new * size_elem);
    memcpy(data_new, vec->data, min(size_new, vec->size) * size_elem);
    free(vec->data);
    vec->data = data_new;
    vec->mem_size = size_new;
    vec->size = min(vec->size, size_new);
}

#define vec_mem_resize(vec, size) {if (size < 0) {printf("vec_mem_resize called with negative number\n"); exit(1);} _vec_mem_resize((void*)vec, sizeof(*vec->data), size);}

static inline void _vec_resize(struct _Vector* vec, size_t size_elem, size_t size_new)
{
    vec->size = size_new;
    if (vec->size > vec->mem_size)
        _vec_mem_resize(vec, size_elem, max(size_new, vec->mem_size * 2));
}

#define vec_resize(vec, size) {if (size < 0) {printf("vec_resize called with negative number\n"); exit(1);} _vec_resize((void*)vec, sizeof(*vec->data), size);}

static inline void _vec_append(struct _Vector* vec, size_t size_elem, void* valptr)
{
    _vec_resize(vec, size_elem, vec->size + 1);
    memcpy((void*)((size_t)vec->data + (vec->size - 1) * size_elem), valptr, size_elem);
}

#define vec_append(vec, val) {if (sizeof(*vec->data) != sizeof(val)) {printf("vec_append called with conflicting types\n"); exit(1);} __auto_type _val = val; _vec_append((void*)vec, sizeof(*vec->data), &_val);}

static inline void _vec_insert(struct _Vector* vec, size_t size_elem, void* valptr, size_t index)
{
    _vec_resize(vec, size_elem, vec->size + 1);
    memcpy((void*)((size_t)vec->data + (index + 1) * size_elem), (void*)((size_t)vec->data + index * size_elem), (vec->size - 1 - index) * size_elem);
    memcpy((void*)((size_t)vec->data + index * size_elem), valptr, size_elem);
}

#define vec_insert(vec, val, index) {if (sizeof(*vec->data) != sizeof(val)) {printf("vec_insert called with conflicting types\n"); exit(1);} if (index < 0 || index > vec->size) {printf("vec_insert called with out of range index\n"); exit(1);} __auto_type _val = val; _vec_insert((void*)vec, sizeof(*vec->data), &_val, index);}

static inline void _vec_erase(struct _Vector* vec, size_t size_elem, size_t first, size_t count)
{
    memcpy((void*)((size_t)vec->data + first * size_elem), (void*)((size_t)vec->data + (first + count) * size_elem), (vec->size - first - count) * size_elem);
    _vec_resize(vec, size_elem, vec->size - count);
}

#define vec_erase(vec, first, count) {if (first < 0 || count < 0 || first + count > vec->size) {printf("vec_erase called with invalid range\n"); exit(1);} _vec_erase((void*)vec, sizeof(*vec->data), first, count)}


#endif
