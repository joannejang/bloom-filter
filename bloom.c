#include "bloom.h"
#include "hash_functions.h"	

#define NUM_BITS 32	 
#define NUM_HASH 2
// #define NUM_BITS 8  

bloom_filter* create_filter(size_t size) {
	bloom_filter *filter = calloc(1, sizeof(struct bloom_filter));
	assert(filter);
	
	filter->size = size;
	filter->bits = calloc(1, NUM_BITS*size);
	return filter;
}

void add_entry(bloom_filter *filter, const void *entry) {
	assert(entry);
	uint32_t *bits = filter->bits;
	
	const char *entry_str = (const char *) entry;
	int length = strlen(entry_str);
	
	uint32_t sfh = hash_SuperFastHash(entry_str, length) % (NUM_BITS*filter->size);
	//uint32_t djb = hash_djb2(entry_str) % (NUM_BITS*filter->size);
	uint32_t jenk = hash_jenkins_one_at_a_time(entry_str, length) % (NUM_BITS*filter->size);
	bits[sfh/NUM_BITS] |= 1 << (sfh % NUM_BITS);
	//((uint32_t *) filter->bits)[djb/NUM_BITS] |= 1 << djb%NUM_BITS;
	bits[jenk/NUM_BITS] |= 1 << (jenk % NUM_BITS);
}

bool possibly_present(bloom_filter *filter, const void *entry) {
	assert(entry);
	uint32_t *bits = (uint32_t *) filter->bits;
	
	const char *entry_str = (const char *) entry;	
	int length = strlen(entry_str);

	uint32_t sfh = hash_SuperFastHash(entry_str, length) % (NUM_BITS*filter->size);
	//uint32_t djb = hash_djb2(entry_str) % (NUM_BITS*filter->size);
	uint32_t jenk = hash_jenkins_one_at_a_time(entry_str, length) % (NUM_BITS*filter->size);

	return ((bits[sfh/NUM_BITS] & 1 << (sfh % NUM_BITS)) &&
	//	(bits[djb/NUM_BITS] |= 1 << djb) &&
		(bits[jenk/NUM_BITS] |= 1 << (jenk % NUM_BITS)));
}

void free_filter(bloom_filter *filter) {
	if (!filter) return;
	free(filter->bits);
	free(filter);
}
