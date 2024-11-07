#include <stdio.h>
#include <stdlib.h>
#include "../list.h"

void ListTest(void) {
	dlist_t *list = DlistCreate();
	DlistDestroy(list);

	list = DlistCreate();

	for (int i = 0; i < 100; i++) {
		int *x = (int *)malloc(sizeof(int));
		*x = i;
		DlistAppend(list, (void *)x);
	}

	llnode_t *np = DlistGetHead(list);
	for (; np != NULL; np = np->next) {
		int *data = (int *)np->data;
		printf("%d%s", *data, (np->next == NULL) ? "\n" : " -> ");
	}

	DlistDestroy(list);
}

