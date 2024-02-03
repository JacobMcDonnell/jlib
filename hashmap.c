#include "hashmap.h"

/* getHashInt: wrapper for non array keys */
uint64_t getHashInt(uint8_t key)
{
	return getHash(&key, 1);
}

/* getHash: implementation of FNV-1 hash algorithm 64-bit */
uint64_t getHash(const uint8_t *key, size_t length)
{
	const uint64_t prime = 1099511628211;	// FNV_prime 64-bits
	uint64_t hash = 14695981039346656037ull; // FNV_offset 64-bits

	for (int i = 0; i < length; i++) {
		hash *= prime;
		hash ^= key[i];
	}
	return hash;
}

