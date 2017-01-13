#ifndef _BLOOM_H
#define _BLOOM_H

#include <stdbool.h> // bool
#include <stdlib.h> // like, everything
#include <assert.h> // unit tests
#include <stdio.h> // print statements
#include <stdint.h> // int in hash functions
#include <string.h> // strlen in hash functions
#include <math.h> // ceil

typedef struct bloom_filter {
	void *bits;
	size_t size;
	int m;
	int k;
} bloom_filter;

bloom_filter* create_filter(size_t size);

void free_filter(bloom_filter *filter);

void add_entry(bloom_filter *filter, const void *entry);

bool possibly_present(bloom_filter *filter, const void *entry);



#endif