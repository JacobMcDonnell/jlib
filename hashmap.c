#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

/* getHash: implementation of FNV-1 hash algorithm 64-bit */
uint64_t GetHash( const char * const key, const size_t length ) {
	const uint64_t prime = 1099511628211;	// FNV_prime 64-bits
	uint64_t hash = 14695981039346656037ull; // FNV_offset 64-bits

	for ( int i = 0; i < length; i++ ) {
		hash *= prime;
		hash ^= key[i];
	}
	return hash;
}

/* HashMapCreate: return a pointer to a new empty hashmap */
hashmap_t *HashMapCreate( size_t length ) {
	hashmap_t *map = ( hashmap_t * )malloc( sizeof(hashmap_t) );
	map->length = length;
	map->members = ( hnode_t ** )calloc( sizeof( hnode_t * ), length );
	memset( map->members, NULL, sizeof( map->members ) );
	return map;
}

/* HashMapAdd: add a key value pair to a hashmap and return pointer to node */
void *HashMapAdd( hashmap_t *map, char *key, void *data ) {
	int hash = GetHash( key, strlen( key ) );
	hnode_t *member = map->members[hash];
	if ( member == NULL ) {
		member->key = strdup( key );
		member->data = data;
	} else if ( strcmp( member->key, key ) == 0 ) {
		member->data = data;
	} else {
		for ( int j = 1, i = hash + 1; i < map->length; j++, i += j * j ) {
			member = map->members[i];
			if ( member == NULL ) {
				member->key = strdup( key );
				member->data = data;
			} else if ( strcmp( member->key, key ) == 0 ) {
				member->data = data;
			}
		}
	}
}

/* HashMapGet: return the value for a key or EOF if it doesn't exist */
void *HashMapGet( hashmap_t *map, char *key ) {
	int hash = GetHash( key, strlen( key ) );
}

/* HashMapDeleteKey: delete a member from the table based on the key */
int HashMapDeleteKey( hashmap_t *map, char *key ) {
}
