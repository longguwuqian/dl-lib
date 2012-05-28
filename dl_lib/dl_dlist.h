#include "dl_common.h"
#define DLIST(name, type)                                                                                      \
struct  {                                                                                                                 \
	struct type *head, *tail, *pre, *cur;                                                                        \
	int length;                                                                                                           \
} name;

#define DLIST_INIT(dlist)                                                                                        \
do {                                                                                                                       \
	dlist->head = malloc(sizeof(*dlist->head));                                                            \
	__check_malloc_fail(dlist)
}