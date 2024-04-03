#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED

//Credits to Theelf111 for this
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

#define declVec(type) \
struct type ## _vec \
{ \
    size_t size; \
    size_t mem_size; \
    type* data; \
}; \
static struct type ## _vec*type ## _vec(size_t size_i) \
{ \
    struct type ## _vec* vec = malloc(sizeof(struct type ## _vec)); \
    vec->size = size_i; \
    vec->mem_size = size_i; \
    vec->data = malloc(size_i * sizeof(type)); \
    memset(vec->data, 0, sizeof(vec->data) * sizeof(type)); \
    return vec; \
} \
static void type ## _vec_mem_resize(struct type ## _vec* vec, size_t size_new) \
{ \
    type* data_new = malloc(size_new * sizeof(type)); \
    memset(data_new, 0, size_new * sizeof(type)); \
    memcpy(data_new, vec->data, min(size_new, vec->size) * sizeof(type)); \
    free(vec->data); \
    vec->data = data_new; \
    vec->mem_size = size_new; \
    vec->size = min(vec->size, size_new); \
} \
static void type ## _vec_resize(struct type ## _vec* vec, size_t size_new) \
{ \
    vec->size = size_new; \
    if (vec->size > vec->mem_size) \
        type ## _vec_mem_resize(vec, max(size_new, vec->mem_size * 2)); \
} \
static void type ## _vec_append(struct type ## _vec* vec, type val) \
{ \
    type ## _vec_resize(vec, vec->size + 1); \
    vec->data[vec->size-1] = val; \
} \
static void type ## _vec_insert(struct type ## _vec* vec, type val, size_t index) \
{ \
    type ## _vec_resize(vec, vec->size + 1); \
    memcpy(&vec->data[index + 1], &vec->data[index], (vec->size - 1 - index) * sizeof(type)); \
    vec->data[index] = val; \
} \
static void type ## _vec_erase(struct type ## _vec* vec, size_t first, size_t count) \
{ \
    memcpy(&vec->data[first], &vec->data[first + count], (vec->size - first - count) * sizeof(type)); \
    type ## _vec_resize(vec, vec->size - count); \
}

#define free_vec(vec) { free(vec->data);free(vec); }

#endif