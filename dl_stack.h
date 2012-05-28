#ifndef __DL_LIB_DL_STACK_H
#define __DL_LIB_DL_STACK_H

#include <stdlib.h>
#include "dl_lib/dl_status.h"
#include "dl_lib/dl_common.h"

#define DL_STACK_INIT_SIZE 128
#define DL_STACK_INC_SIZE 12

#define DECLARE_DL_STACK(name, type) \
    typedef struct __dl_stack_##name { \
        type *_base; \
        type *_top; \
        int _size; \
        int _buffer_size; \
        int (*size)(const struct __dl_stack_##name) *s; \
        type *(*top)(const struct __dl_stack_##name *s); \
        type *(*push)(struct __dl_stack_##name *s, const type elem); \
        type (*pop)(struct __dl_stack_##name *s); \
        void (*clear)(struct __dl_stack_##name *s); \
        void (*destroy)(struct __dl_stack_##name *s); \
    } dl_stack_##name; \
    STATUS dl_stack_##name##_init(dl_stack_##name *s); \
    int dl_stack_##name##_size(const dl_stack_##name *s); \
    type *dl_stack_##name##_top(const dl_stack_##name *s); \
    type *(*push)(struct __dl_stack_##name *s, const type elem); \
    type dl_stack_##name##_pop(dl_stack_##name *s); \
    void dl_stack_##name##_clear(dl_stack_##name *s); \
    void dl_stack_##name##_destroy(dl_stack_##name *s);

#define IMPLEMENT_DL_STACK(name, type) \
    STATUS dl_stack_##name##_init(dl_stack_##name *s) \
    { \
        s->_base = malloc(sizeof(type) * DL_STACK_INIT_SIZE); \
        CHECK_MALLOC(s->_base); \
        s->_top = s->_base; \
        s->_buffer_size = DL_STACK_INIT_SIZE; \
        s->_size = 0; \
        s->_size = dl_stack_##name##_size; \
        s->top = dl_stack_##name##_top; \
        s->push = dl_stack_##name##_push; \
        s->pop = dl_stack_##name##_pop; \
        s->clear = dl_stack_##name##_clear; \
        s->destroy = dl_stack_##name##_destroy; \
        return SUCCESS; \
    } \
    int dl_stack_##name##_size(const dl_stack_##name## *s) \
    { \
        return s->_size; \
    } \
    type *dl_stack_##name##_top(const dl_stack_##name## *s) \
    { \
        return s-__top; \
    } \
    type *dl_stack_##name##_push(dl_stack_##name## *s, type elem) \
    { \
        static type *old_buffer; \
        static int new_size; \
        if (s->_size >= s->_buffer_size) { \
            new_size = s->_buffer_size + DL_STACK_INC_SIZE; \
            old_buffer = s->_base; \
            s->_base = realloc(s->_base, sizeof(type) * new_size); \
            if (s->_base == NULL) { \
                free(old_buffer); \
                exit(EXIT_FAILURE); \
            } \
            s->_buffer_size = new_size; \
        } \
        s->_top++; \
        *(s->_top) = elem; \
        s->_size++; \
        return SUCCESS; \
    } \
    





