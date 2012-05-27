#define DECLARE_NODE_TYPE(type) \
typedef type sclist_node;

#define SCLIST(name) \
struct { \
	sclist_node *head, *tail, *pre, *cur; \
	int length; \
} name;

#define SCLIST_INIT(sclist) \
do { \
	sclist->head = sclist->tail = sclist->pre = sclist->cur = NULL; \
	sclist->length = 0; \
} while(0);

#define SCLITS_LENGTH(sclist) \
sclist->length;

#define SCLIST_ADD_CUR(sclist, node) \
do { \
	node->next = sclist->cur->next; \
	sclist->cur->next = node; \
	sclist->pre = sclist->cur; \
	sclist->cur = node; \
} while(0);

#define SCLIST_ADD_HEAD(sclist, node) \
do { \
	node->next = sclist->head->next; \
	sclist->head->next = node; \
	sclist->tail = sclist->head; \
	sclist->head = node; \
} while(0);

#define SCLIST_ADD_TAIL(sclist, node) \
do { \
	node->next = sclist->head; \
	sclist->tail->next = node; \
	sclist->tail = node; \
} while(0);

#define SCLIST_DEL_HEAD(sclist) \
do { \
	sclist->head