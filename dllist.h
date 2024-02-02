#include <stdlib.h>

#define llinit(name, dataType) \
	int ll##name##_t_size = 0; \
	typedef struct ll##name##_t { \
		dataType data; \
		struct ll##name##_t *next; \
		struct ll##name##_t *prev; \
	} ll##name##_t; \
	llimple(name, dataType);

#define llimple(name, dataType) \
	void ll##name##_add(ll##name##_t *node, dataType c) { \
		node->next = (ll##name##_t *)malloc(sizeof(ll##name##_t)); \
		node->next->prev = node; \
		node->next->data = c; \
		node->next->next = NULL; \
		ll##name##_t_size++; \
	} \
	void ll##name##_delete(ll##name##_t *node) { \
		node->prev->next = node->next; \
		node->next->prev = node->prev; \
		free((void *)node); \
		ll##name##_t_size--; \
	} \
	ll##name##_t *ll##name##_get(ll##name##_t *rp, int n) { \
		if (n >= ll##name##_t_size) \
			return NULL; \
		ll##name##_t *lp; \
		int i; \
		for (lp = rp, i = 0; lp != NULL && i < n; i++, lp = lp->next) \
			; \
		return lp; \
	}
