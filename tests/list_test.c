#include <stdio.h>
#include <stdlib.h>
#include "../list.h"

void ListTest( void ) {
	dlist_t *list = DlistCreate();

	for ( int i = 0; i < 100; i++ ) {
		int *x = ( int * )malloc( sizeof( int ) );
		*x = i;
		DlistAddEnd( list, ( void * )x );
	}

	llnode_t *np = list->head.next;
	for ( ; np != &( list->tail ); np = np->next ) {
		int *data = ( int * )np->data;
		printf( "%d%s", *data, ( np->next == &( list->tail ) ) ? "\n" : " -> " );
	}

	DlistDestroyList( list );
}
