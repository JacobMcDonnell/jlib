#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

dlist_t *DlistCreate(void) {
	dlist_t *temp = (dlist_t *)malloc(sizeof(dlist_t));
	if (temp == NULL)
		return NULL;
	temp->size = 0;
	temp->head = NULL;
	temp->tail = NULL;
	return temp;
}

static inline llnode_t *NodeCreate(void *data) {
	llnode_t *new = (llnode_t *)malloc(sizeof(llnode_t));
	if (new == NULL)
		return NULL;
	new->data = data;
	new->next = NULL;
	new->prev = NULL;
	return new;
}

void DlistAddAfter(dlist_t *const list, llnode_t *node, void *data) {
	llnode_t *next, *new = NodeCreate(data);
	if (new == NULL)
		return;
	if (list->size == 0) {
		list->head = new;
		list->tail = new;
		list->size++;
		return;
	}
	next = node->next;
	node->next = new;
	new->prev = node;
	if (next != NULL)
		next->prev = new;
	new->next = next;
	list->size++;
	if (node == list->tail)
		list->tail = new;
}

void DlistAddBefore(dlist_t *const list, llnode_t *node, void *data) {
	llnode_t *prev, *new = NodeCreate(data);
	if (new == NULL)
		return;
	if (list->size == 0) {
		list->head = new;
		list->tail = new;
		list->size++;
		return;
	}
	prev = node->prev;
	node->prev = new;
	new->next = node;
	if (prev != NULL)
		prev->next = new;
	new->prev = prev;
	list->size++;
	if (node == list->head)
		list->head = new;
}

inline void DlistAppend(dlist_t *const list, void *data) {
	DlistAddAfter(list, list->tail, data);
}

inline void DlistPrepend(dlist_t *const list, void *data) {
	DlistAddBefore(list, list->head, data);
}

llnode_t *DlistGet(const dlist_t *const list, const int n) {
	llnode_t *lp;
	if (list->size / 2 > n) {
		lp = list->head;
		for (int i = 0; i < list->size && i < n; i++, lp = lp->next)
			;
	} else {
		lp = list->tail;
		for (int i = list->size - 1; i > n && i > 0;
			i++, lp = lp->prev)
			;
	}
	return lp;
}

void *DlistDeleteNode(dlist_t *const list, llnode_t *node) {
	void *data = node->data;
	llnode_t *prev = node->prev, *next = node->next;

	if (prev != NULL)
		prev->next = next;
	if (next != NULL)
		next->prev = prev;

	if (node == list->head)
		list->head = next;
	if (node == list->tail)
		list->tail = prev;

	free((void *)node);
	list->size--;
	return data;
}

void DlistDestroy(dlist_t *list) {
	while (list->size > 0)
		DlistDeleteNode(list, list->head);
	free((void *)list);
}

