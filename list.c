#include "list.h"
#include <stdlib.h>

dlist_t *DlistCreate( void ) {
	dlist_t *temp = ( dlist_t * )malloc( sizeof( dlist_t ) );
	temp->size = 0;
	temp->head = ( llnode_t ){ .data = NULL, .next = &( temp->tail ), .prev = NULL };
	temp->tail = ( llnode_t ){ .data = NULL, .next = NULL, .prev = &( temp->head ) };
	return temp;
}

void DlistAdd( dlist_t * const list, llnode_t *node, void *data ) {
	llnode_t *new = ( llnode_t * )malloc( sizeof( llnode_t ) );
	llnode_t *next = node->next;
	node->next = new;
	new->prev = node;
	next->prev = new;
	new->next = next;
	new->data = data;
	list->size++;
}

void DlistAddEnd( dlist_t * const list, void *data ) {
	DlistAdd( list, list->tail.prev, data );
}

void DlistAddStart( dlist_t * const list, void *data ) {
	DlistAdd( list, &( list->head ), data );
}

llnode_t *DlistGet( const dlist_t * const list, const int n ) {
	llnode_t *lp;
	if ( list->size / 2 > n ) {
		lp = list->head.next;
		for ( int i = 0; lp != &( list->tail ) && i < n; i++, lp = lp->next )
			;
	} else {
		lp = list->tail.prev;
		for ( int i = list->size - 1; i > n && lp != &( list->head ); i++, lp = lp->prev )
			;
	}
	return lp;
}

void DlistDeleteNode( dlist_t * const list, llnode_t *node ) {
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free( ( void * )node );
	node = NULL;
	list->size--;
}

void DlistDestroyList( dlist_t *list ) {
	while ( list->head.next != &( list->tail ) ) {
		DlistDeleteNode( list, list->head.next );
	}
	free( (void *)list );
	list = NULL;
}
