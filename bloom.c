#include "bloom.h"
#include "hash_functions.h"	

#define NUM_BITS 32	   

bloom_filter* create_filter(size_t size) {
	bloom_filter *filter = calloc(1, sizeof(struct bloom_filter));
	assert(filter);
	filter->size = size;
	filter->bits = calloc(1, size); // TODO resolve calloc vs. malloc-- will I need to memset later?!
	return filter;
}

void add_entry(bloom_filter *filter, const void *entry) {
	assert(entry);
	const char *entry_str = *(char **) entry;
	int length = strlen(entry_str);
	uint32_t sfh = hash_SuperFastHash(entry_str, length);
  uint32_t djb = hash_djb2(entry_str);
  uint32_t jenk = hash_jenkins_one_at_a_time(entry_str, length);
  (*(char **) filter->bits)[sfh/NUM_BITS] |= 1 << sfh%NUM_BITS;
  (*(char **) filter->bits)[djb/NUM_BITS] |= 1 << djb%NUM_BITS;
  (*(char **) filter->bits)[jenk/NUM_BITS] |= 1 << jenk%NUM_BITS;
}

bool possibly_present(bloom_filter *filter, const void *entry) {
	return false;
}

void free_filter(bloom_filter *filter) {
  if (!filter) return;
  free(filter->bits);
  free(filter);
}