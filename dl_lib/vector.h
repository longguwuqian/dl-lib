#ifndef __DL_LIB_VECTOR_H
#define __DL_LIB_VECTOR_H

#include <stdlib.h>
#include "dl_lib/dl_status.h"
#include "dl_lib/dl_common.h"

#define VECTOR_INIT_SIZE 128
#define VECTOR_INC_SIZE 128

#define DECLARE_VECTOR_TYPE(vector_type, elem_type) \
    typedef struct __vector_##vector_type { \
    	elem_type *_buffer; \
    	int _buffer_size; \
    	int _size; \
    	elem_type (*at)(const struct __vector_##vector_type *v, int index); \
    	STATUS (*update)(struct __vector_##vector_type *v, int index, elem_type new_elem); \
    	STATUS (*erase)(struct __vector_##vector_type *v, int index); \
    	void (*push_back)(struct __vector_##vector_type *v, elem_type elem); \
        void (*pop_back)(struct __vector_##vector_type *v); \
        int (*empty)(const struct __vector_##vector_type *v); \
    	void (*clear)(struct __vector_##vector_type *v); \
    	int (*size)(const struct __vector_##vector_type *v); \
    	void (*destroy)(struct __vector_##vector_type *v); \
     } vector_type; \
    static inline STATUS    vector_type##_init(vector_type *v); \
    static inline void      vector_type##_push_back(vector_type *v, elem_type elem); \
    static inline void      vector_type##_pop_back(vector_type *v); \
    static inline int       vector_type##_empty(const vector_type *v); \
    static inline STATUS    vector_type##_update(vector_type *v, int index, elem_type elem); \
    static inline STATUS    vector_type##_erase(vector_type *v, int index); \
    static inline void      vector_type##_clear(vector_type *v); \
    static inline void      vector_type##_destroy(vector_type *v); \
    static inline elem_type vector_type##_at(const vector_type *v, int index); \
    static inline int       vector_type##_size(const vector_type *v);

#define IMPLEMENT_VECTOR_TYPE(vector_type, elem_type) \
    STATUS vector_type##_init(vector_type *v) \
    { \
    	v->_size                   = 0; \
    	v->_buffer_size            = VECTOR_INIT_SIZE; \
    	v->_buffer                 = malloc(sizeof(elem_type) * VECTOR_INIT_SIZE); \
    	CHECK_MALLOC(v->_buffer); \
    	v->push_back               = vector_type##_push_back; \
        v->pop_back                = vector_type##_pop_back; \
        v->empty                   = vector_type##_empty; \
    	v->at                      = vector_type##_at; \
    	v->size                    = vector_type##_size; \
    	v->update                  = vector_type##_update; \
    	v->erase                   = vector_type##_erase; \
    	v->clear                   = vector_type##_clear; \
    	v->destroy                 = vector_type##_destroy; \
    	return SUCCESS; \
    } \
    void vector_type##_push_back(vector_type *v, elem_type elem) \
    { \
    	static int new_size; \
    	static elem_type *old_buffer; \
    	if (v->_size >= v->_buffer_size) { \
    	    new_size = v->_buffer_size + VECTOR_INC_SIZE; \
    	    old_buffer = v->_buffer; \
	        v->_buffer = realloc(v->_buffer, sizeof(elem_type) * new_size); \
    	    if (v->_buffer == NULL) { \
    	    	free(old_buffer); \
    	    	exit(EXIT_FAILURE); \
    	    } \
    	    v->_buffer_size = new_size; \
    	} \
    	v->_buffer[(v->_size)++] = elem; \
    } \
    void vector_type##_pop_back(vector_type *v) \
    { \
        if (v->_size != 0) v->_size--; \
    }\
    int vector_type##_empty(const vector_type *v) \
    { \
        return v->_size == 0 ? 1 : 0; \
    } \
    elem_type vector_type##_at(const vector_type *v, int index) \
    { \
    	if (index < 0) return v->_buffer[0]; \
    	else if (index >= v->_size) return v->_buffer[v->_size - 1]; \
    	else return v->_buffer[index]; \
    } \
    STATUS vector_type##_update(vector_type *v, int index, elem_type elem) \
    { \
    	if (v->_size > index && index >= 0) { \
    	    v->_buffer[index] = elem; \
	        return SUCCESS; \
    	} \
    	else \
    	    return ERROR; \
    } \
    STATUS vector_type##_erase(vector_type *v, int index) \
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
    int vector_type##_size(const vector_type *v) \
    { \
    	return v->_size; \
    } \
    void vector_type##_clear(vector_type *v) \
    { \
    	v->_size = 0; \
    } \
    void vector_type##_destroy(vector_type *v) \
    { \
    	v->_size = 0; \
    	v->_buffer_size = 0; \
    	free(v->_buffer); \
    }

#define VECTOR_TEMPLATE(vector_type, elem_type) \
    DECLARE_VECTOR_TYPE(vector_type, elem_type) \
    IMPLEMENT_VECTOR_TYPE(vector_type, elem_type)

#endif
