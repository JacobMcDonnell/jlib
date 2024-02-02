#include <stdio.h>
#include "llnode.h"

#define Var(type, name, value) type name = value

llinit(32, char);
llinit(char, char*);

int main(void)
{
	Var(char, c, 'A');
	Var(int, x, 5);
	printf("%c\t%d\n", c, x);

	ll32_t root;
	root.prev = NULL;
	root.data = 'A';
	ll32_t *rp = &root;
	for (char c = 'B'; c <= 'Z'; c++) {
		ll32_add(rp, c);
		rp = rp->next;
	}

	rp = ll32_get(&root, 2);

	printf("%c\n", rp->data);

	ll32_delete(rp);

	for (rp = &root; rp != NULL; rp = rp->next) {
		printf("%c ", rp->data);
	}
}
