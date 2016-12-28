#ifndef _BLOOM_H
#define _BLOOM_H

#include <stdbool.h> // bool
#include <stdlib.h> // like, everything
#include <assert.h> // unit tests
#include <stdio.h> // print statements
#include <stdint.h> // int in hash functions
#include <string.h> // strlen in hash functions

typedef struct bloom_filter {
	void *bits;
	size_t size;
} bloom_filter;

bloom_filter* create_filter(size_t size);

void free_filter(bloom_filter *filter);

void add_entry(bloom_filter *filter, const void *entry);

bool possibly_present(bloom_filter *filter, const void *entry);

uint32_t SuperFastHash(const char *data, int len);

uint32_t djb2(const char *str);

uint32_t jenkins_one_at_a_time_hash(const char *data, int len);

#endif