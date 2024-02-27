#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdint.h>
#include <stddef.h>

typedef struct hnode_t {
	void *data;
	char *key;
} hnode_t;

typedef struct hashmap_t {
	size_t length;
	hnode_t **members;
} hashmap_t;

uint64_t getHash( const char * const key, const size_t length );
hashmap_t *HashMapCreate( void );
void *HashMapAdd( hashmap_t *map, char *key, void *data );
void *HashMapGet( hashmap_t *map, char *key );
int HashMapDeleteKey( hashmap_t *map, char *key );

#endif //HASHMAP_H
