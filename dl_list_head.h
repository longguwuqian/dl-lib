#ifndef _DLCOMMON_DL_LIST_HEAD_H
#define _DLCOMMON_DL_LIST_HEAD_H

#ifdef _WIN32
#define inline 
#endif

struct __list_head {
	struct __list_head *prev;
	struct __list_head *next;
};
typedef struct __list_head list_head;
#define LIST_HEAD(name) struct __list_head name = { &(name), &(name)};
#define INIT_LIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); \
	(ptr)->prev = (ptr); \
}while (0)
static inline int list_empty(const struct __list_head *head)
{
	return head->next == head;
}
static inline void __list_add(struct __list_head *new,struct __list_head *prev,struct __list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}
static inline void list_add(struct __list_head *new,struct __list_head *head)
{
	__list_add(new,head,head->next);
}
static inline void list_add_tail(struct __list_head *new,struct __list_head *head)
{
	__list_add(new,head->prev,head);
}
static inline void __list_del(struct __list_head *prev,struct __list_head *next)
{
	next->prev = prev;
	prev->next = next;
}
static inline void list_del(struct __list_head *entry)
{
	__list_del(entry->prev,entry->next);
	INIT_LIST_HEAD(entry);
}

static inline void list_step(struct __list_head **pos, struct __list_head *head, int step)
{
	if (head->next->next == head) return;
	while (step--) {
		*pos = (*pos)->next;
		if (*pos == head) *pos = (*pos)->next;
	}
}

#define list_entry(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); \
			pos = pos->next)
#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
			pos = n, n = pos->next)

#endif