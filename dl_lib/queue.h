#ifndef _DL_LIB_QUEUE_H
#define _DL_LIB_QUEUE_H

#include <assert.h>

struct __queue_node {
    struct __queue_node *next;
};

typedef struct __queue_node queue_node;

struct queue {
    queue_node *head;
    queue_node *tail;
    long length;
};

#define queue_entry(ptr,type,member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

static inline void init_queue(struct queue *queue)
{
    queue->head = queue->tail = NULL;
    queue->length = 0;
}

static inline int queue_empty(const struct queue *queue)
{
    assert(queue != NULL);
    assert((queue->head == NULL && queue->tail == NULL) || (queue->head != NULL) || (queue->head == NULL && queue->length == 0));
    return queue->head == NULL;
}

static inline void queue_add(queue_node *node,struct queue *queue)
{
    assert(node != NULL && queue != NULL);
    if(queue_empty(queue)) {
        queue->head = queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }
    queue->length++;
}
static inline queue_node* queue_del(struct queue *queue)
{
    assert(queue != NULL);
    queue_node *old_head = queue->head;
    if (queue_empty(queue)) return NULL;
    queue->head = old_head->next;
    queue->length--;
    if (queue->length == 0) queue->head = queue->tail = NULL;
    return old_head;
}

static inline int queue_length(struct queue *queue)
{
    assert(queue != NULL);
    assert(queue->length >= 0);
    return queue->length;
}

#endif
