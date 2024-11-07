#ifndef LIST_H
#define LIST_H
#include <stddef.h>

#define DlistGetSize(X)	((X)->size)
#define DlistGetHead(X)	((X)->head)
#define DlistGetTail(X)	((X)->tail)

typedef struct llnode_t {
	void *data;
	struct llnode_t *next;
	struct llnode_t *prev;
} llnode_t;

typedef struct dlist_t {
	llnode_t *head;
	llnode_t *tail;
	size_t size;
} dlist_t ;

dlist_t *DlistCreate(void);
void DlistAddAfter(dlist_t * const list, llnode_t *node, void *data);
void DlistPrepend(dlist_t * const list, void *data);
void DlistAppend(dlist_t * const list, void *data);
llnode_t *DlistGet(const dlist_t * const list, const int n);
void *DlistDeleteNode(dlist_t * const list, llnode_t *node);
void DlistDestroy(dlist_t *list);

#endif
