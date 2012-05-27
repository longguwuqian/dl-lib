#include <stddef.h>
#include <stdlib.h>
#define DCLIST_NODE_TYPE(type) \
typedef type dclist_node_type; \
typedef struct dclist_type { \
			dclist_node_type *head; \
			int length; \
		} DCLIST_TYPE;

#define DCLIST(name) \
DCLIST_TYPE name;

#define DCLIST_INIT(dclist) \
do { \
	(dclist)->head = NULL; \
	(dclist)->length = 0; \
} while(0)

#define DCLIST_LENGTH(dclist) \
((dclist)->length)

#define DCLIST_EMPTY(dclist) \
((dclist)->length == 0)

#define DCLIST_FIRST(dclist) \
((dclist)->head)

#define DCLIST_LAST(dclist, pfield) \
((dclist)->head->pfield)

#define DCLIST_MOVE_NEXT(dclist, pos, nfield) \
((pos) = (pos)->nfield)

#define DCLIST_MOVE_PREV(dclist, pos, pfield) \
((pos) = (pos)->pfield)

#define DCLIST_NEXT(dclist, pos, nfield) \
((pos)->nfield)

#define DCLIST_PREV(dclist, pos, pfield) \
((pos)->pfield)

#define DCLIST_ADD_HEAD(dclist, node, pfield, nfield) \
do { \
	if ((dclist)->length == 0) { \
		(node)->nfield = (node)->pfield = (node); \
	} else { \
		(node)->pfield = (dclist)->head->pfield; \
		(node)->nfield = (dclist)->head; \
		(dclist)->head->pfield->nfield = (node); \
		(dclist)->head->pfield = (node); \
	} \
	(dclist)->head = (node); \
	(dclist)->length++; \
} while(0)

#define DCLIST_ADD_BEFORE(dclist, node, pos, pfield, nfield) \
do { \
	(node)->pfield = (pos)->pfield; \
	(node)->nfield = (pos); \
	(pos)->pfield->nfield = (node); \
	(pos)->pfield = (node); \
	(dclist)->length++; \
} while(0)

#define DCLIST_ADD_AFTER(dclist, node, pos, pfield, nfield) \
do { \
	(node)->pfield = (pos); \
	(node)->nfield = (pos)->nfield; \
	(pos)->nfield->pfield = (node); \
	(pos)->nfield = (node); \
	(dclist)->length++; \
} while(0)

#define DCLIST_DEL_HEAD(dclist, pfield, nfield) \
do { \
	if ((dclist)->length != 0) { \
		if ((dclist)->length == 1) { \
			(dclist)->head = NULL; \
		} else { \
			(dclist)->head->pfield->nfield = (dclist)->head->nfield; \
			(dclist)->head->nfield->pfield = (dclist)->head->pfield; \
			(dclist)->head = (dclist)->head->nfield; \
		} \
		(dclist)->length--; \
	} \
} while(0)

#define DCLIST_DEL(dclist, pos, pfield, nfield) \
do { \
	if ((dclist)->length) (dclist)->length--; \
	if ((dclist)->head == (pos) && ((dclist)->head->nfield == (dclist)->head)) { \
		(dclist)->head = (pos) = NULL; \
	} else { \
		(pos)->nfield->pfield = (pos)->pfield; \
		(pos)->pfield->nfield = (pos)->nfield; \
		if ((pos) == (dclist)->head) \
			(dclist)->head=(pos)->nfield; \
		(pos) = (pos)->nfield; \
	} \
} while(0)

#define DCLIST_FOR_EACH(dclist, pos, nfield) \
for ((pos) = (dclist)->head; (pos) != NULL; (pos) = ((pos)->nfield == (dclist)->head ? NULL : (pos)->nfield))
	
#define DCLIST_FOR_EACH_PREV(dclist, pos, pfield) \
for ((pos) = (dclist)->head; (pos) != NULL; (pos) = ((pos)->pfield == (dclist)->head ? NULL : (pos)->pfield))

#define DCLIST_SEARCH_SCALAR(dclist, pos, field, key, nfield) \
do { \
	DCLIST_FOR_EACH(dclist, pos, nfield) { \
		if ((pos)->field == key) break; \
	} \
} while(0)

#define DCLIST_SEARCH(dclist, pos, cmp, elem, nfield) \
do { \
	DCLIST_FOR_EACH(dclist, pos) { \
		if ((cmp(pos, elem)) == 0) break; \
	} \
} while(0)

#define DCLIST_EXCHANGE_NODE(dclist, pos1, pos2, pfield, nfield) \
do { \
	if ((pos1) != NULL && (pos2) != NULL && (pos1) != (pos2)) { \
		(pos1)->nfield = (dclist_node_type *)((size_t)((pos1)->nfield) ^ (size_t)((pos2)->nfield)); \
		(pos2)->nfield = (dclist_node_type *)((size_t)((pos2)->nfield) ^ (size_t)((pos1)->nfield)); \
		(pos1)->nfield = (dclist_node_type *)((size_t)((pos1)->nfield) ^ (size_t)((pos2)->nfield)); \
		(pos1)->pfield = (dclist_node_type *)((size_t)((pos1)->pfield) ^ (size_t)((pos2)->pfield)); \
		(pos2)->pfield = (dclist_node_type *)((size_t)((pos2)->pfield) ^ (size_t)((pos1)->pfield)); \
		(pos1)->pfield = (dclist_node_type *)((size_t)((pos1)->pfield) ^ (size_t)((pos2)->pfield)); \
		(pos2)->nfield->pfield = (pos2); \
		(pos2)->pfield->nfield = (pos2); \
		(pos1)->pfield->nfield = (pos1); \
		(pos1)->nfield->pfield = (pos1); \
	} \
} while(0)