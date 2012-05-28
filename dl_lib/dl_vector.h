#ifndef __DL_LIB_DL_VECTOR_H
#define __DL_LIB_DL_VECTOR_H

#include <stdlib.h>
#include "dl_lib/dl_status.h"
#include "dl_lib/dl_common.h"

#define DL_VECTOR_INIT_SIZE 128
#define DL_VECTOR_INC_SIZE 128

#define DECLARE_DL_VECTOR(name, type) \
    typedef struct __dl_vector_##name { \
    	type *_buffer; \
    	int _buffer_size; \
    	int _size; \
    	type *array; \
    	type (*at)(const struct __dl_vector_##name *v, int index); \
    	STATUS (*update)(struct __dl_vector_##name *v, int index, type data); \
    	STATUS (*erase)(struct __dl_vector_##name *v, int index); \
    	void (*push_back)(struct __dl_vector_##name *v, type data); \
        void (*pop_back)(struct __dl_vector_##name *v); \
        int (*empty)(const struct __dl_vector_##name *v); \
    	void (*clear)(struct __dl_vector_##name *v); \
    	int (*size)(const struct __dl_vector_##name *v); \
    	void (*destroy)(struct __dl_vector_##name *v); \
     } dl_vector_##name; \
    STATUS dl_vector_##name##_init(dl_vector_##name *v); \
    void dl_vector_##name##_push_back(dl_vector_##name *v, type data); \
    void dl_vector_##name##_pop_back(dl_vector_##name *v); \
    int    dl_vector_##name##_empty(const dl_vector_##name *v); \
    STATUS dl_vector_##name##_update(dl_vector_##name *v, int index, type data); \
    STATUS dl_vector_##name##_erase(dl_vector_##name *v, int index); \
    void   dl_vector_##name##_clear(dl_vector_##name *v); \
    void   dl_vector_##name##_destroy(dl_vector_##name *v); \
    type   dl_vector_##name##_at(const dl_vector_##name *v, int index); \
    int    dl_vector_##name##_size(const dl_vector_##name *v);

#define IMPLEMENT_DL_VECTOR(name, type) \
    STATUS dl_vector_##name##_init(dl_vector_##name *v) \
    { \
    	v->_size = 0; \
    	v->_buffer_size = DL_VECTOR_INIT_SIZE; \
    	v->_buffer = malloc(sizeof(type) * DL_VECTOR_INIT_SIZE); \
    	CHECK_MALLOC(v->_buffer); \
    	v->array = v->_buffer; \
    	v->push_back = dl_vector_##name##_push_back; \
        v->pop_back = dl_vector_##name##_pop_back; \
        v->empty = dl_vector_##name##_empty; \
    	v->at = dl_vector_##name##_at; \
    	v->size = dl_vector_##name##_size; \
    	v->update = dl_vector_##name##_update; \
    	v->erase = dl_vector_##name##_erase; \
    	v->clear = dl_vector_##name##_clear; \
    	v->destroy = dl_vector_##name##_destroy; \
    	return SUCCESS; \
    } \
    void dl_vector_##name##_push_back(dl_vector_##name *v, type data) \
    { \
    	static int new_size; \
    	static type *old_buffer; \
    	if (v->_size >= v->_buffer_size) { \
    	    new_size = v->_buffer_size + DL_VECTOR_INC_SIZE; \
    	    old_buffer = v->_buffer; \
	        v->_buffer = realloc(v->_buffer, sizeof(type) * new_size); \
    	    if (v->_buffer == NULL) { \
    	    	free(old_buffer); \
    	    	exit(EXIT_FAILURE); \
    	    } \
    	    v->array = v->_buffer; \
    	    v->_buffer_size = new_size; \
    	} \
    	v->_buffer[(v->_size)++] = data; \
    } \
    void dl_vector_##name##_pop_back(dl_vector_##name *v) \
    { \
        if (v->_size != 0) v->_size--; \
    }\
    int dl_vector_##name##_empty(const dl_vector_##name *v) \
    { \
        return v->_size == 0 ? 1 : 0; \
    } \
    type dl_vector_##name##_at(const dl_vector_##name *v, int index) \
    { \
    	if (index < 0) return v->_buffer[0]; \
    	else if (index >= v->_size) return v->_buffer[v->_size - 1]; \
    	else return v->_buffer[index]; \
    } \
    STATUS dl_vector_##name##_update(dl_vector_##name *v, int index, type data) \
    { \
    	if (v->_size > index && index >= 0) { \
    	    v->_buffer[index] = data; \
	        return SUCCESS; \
    	} \
    	else \
    	    return ERROR; \
    } \
    STATUS dl_vector_##name##_erase(dl_vector_##name *v, int index) \
    { \
    	static int i; \
    	i = 0; \
    	if (v->_size > index && index >= 0) { \
    	    for (i = index; i < v->_size - 1; i++) { \
        		v->_buffer[i] = v->_buffer[i + 1]; \
    	    } \
    	    v->_size--; \
	        return SUCCESS; \
    	} else { \
    	    return ERROR; \
    	} \
    } \
    int dl_vector_##name##_size(const dl_vector_##name *v) \
    { \
    	return v->_size; \
    } \
    void dl_vector_##name##_clear(dl_vector_##name *v) \
    { \
    	v->_size = 0; \
    } \
    void dl_vector_##name##_destroy(dl_vector_##name *v) \
    { \
    	v->_size = 0; \
    	v->_buffer_size = 0; \
    	free(v->_buffer); \
    }

#define DL_VECTOR_TEMPLATE(name, type) \
    DECLARE_DL_VECTOR(name, type) \
    IMPLEMENT_DL_VECTOR(name, type)

#define DL_VECTOR(name, var) \
    dl_vector_##name var;

#define DL_VECTOR_INIT(name, pvar) \
    dl_vector_##name##_init(pvar);

#endif
