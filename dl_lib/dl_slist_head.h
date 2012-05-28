#ifndef _DL_COMMON_DL_SLIST_HEAD_H
#define _DL_COMMON_DL_SLIST_HEAD_H

typedef struct slist_head {
	struct slist_head *next;
} slist_head;

#define SLIST_HEAD(name) struct slist_head name = {&(name)};

#define INIT_SLIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); \
}while (0)
	
static inline int slist_empty(const struct slist_head *head)
{
	return head->next == head;
}

static inline void slist_add(slist_head *new,slist_head *head)
{
	new->next = head->next;
	head->next = new;
}

static inline void slist_del(slist_head *prev,slist_head *next)
{
	prev->next->next = NULL;
	prev->next = next;
}

static inline void slist_step(slist_head **pos, slist_head *head, int step)
{
	if (head->next->next == head) return;
	while (step--) {
		*pos = (*pos)->next;
		if (*pos == head) *pos = (*pos)->next;
	}
}

#define slist_entry(ptr,type,member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define slist_for_each(pos,head) \
	for (pos = (head)->next;pos != (head); \
			pos = pos->next)

#define slist_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
			pos = n, n = pos->next)

#endif