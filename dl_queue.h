#ifndef _DL_COMMON_DL_QUEUE_H
#define _DL_COMMON_DL_QUEUE_H
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
    queue->head = queue->tail = 0;
    queue->length = 0;
}

static inline int queue_empty(const struct queue *queue)
{
    return queue->head == 0;
}

static inline void queue_add(queue_node *node,struct queue *queue)
{
        if(queue_empty(queue)) {
                queue->head = queue->tail = node;
        }
        else {
                queue->tail->next = node;
                queue->tail = node;
        }
        queue->length++;
}
static inline queue_node* queue_del(struct queue *queue)
{
        queue_node *head = queue->head;
        queue->head = head->next;
        queue->length--;
        return head;
}

static inline int queue_length(struct queue *queue)
{

        return queue->length;
}

#endif