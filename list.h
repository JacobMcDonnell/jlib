//
// Created by Jacob McDonnell on 2/21/24.
//

#ifndef LIST_H
#define LIST_H
#include <stddef.h>

typedef struct llnode_t {
	void *data;
	struct llnode_t *next;
	struct llnode_t *prev;
} llnode_t;

typedef struct dlist_t {
	llnode_t head;
	llnode_t tail;
	size_t size;
} dlist_t ;

dlist_t *DlistCreate( void );
void DlistAdd( dlist_t * const list, llnode_t *node, void *data );
void DlistAddStart( dlist_t * const list, void *data );
void DlistAddEnd( dlist_t * const list, void *data );
llnode_t *DlistGet( const dlist_t * const list, const int n );
void DlistDeleteNode( dlist_t * const list, llnode_t *node );
void DlistDestroyList( dlist_t *list );

#endif //LIST_H
