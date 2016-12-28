#ifndef _BLOOM_H
#define _BLOOM_H

#include <stdbool.h>

typedef struct bloom_filter {
	void *bits;
	size_t size;
};

bloom_filter* create_filter(size_t size);

void free_filter(bloom_filter *filter);

void add_entry(bloom_filter *filter, const void *entry);

bool possibly_present(bloom_filter *filter, const void *entry);


#endif