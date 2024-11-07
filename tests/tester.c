#include <stdio.h>
#include "list_test.c"
#include "map_test.c"

int main( void ) {
	printf("Testing List:\n");
    ListTest();
	printf("Testing Map:\n");
	MapTest();
	return 0;
}
