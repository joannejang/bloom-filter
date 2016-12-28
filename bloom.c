#include "bloom.h"

// for SuperFastHash
#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif
						   

bloom_filter* create_filter(size_t size) {
	bloom_filter *filter = calloc(1, sizeof(struct bloom_filter));
	assert(filter);
	filter->size = size;
	filter->bits = calloc(1, size); // TODO resolve calloc vs. malloc-- will I need to memset later?!
	return filter;
}

void free_filter(bloom_filter *filter) {
	if (!filter) return;
	free(filter->bits);
	free(filter);
}

void add_entry(bloom_filter *filter, const void *entry) {
	assert(entry);
	char *entry_str = *(char **) entry;
	int length = strlen(entry_str);
	uint32_t sfh = SuperFastHash(entry_str, length) % filter->size;
}

bool possibly_present(bloom_filter *filter, const void *entry) {
	return false;
}

/************* Hash Functions ***********/

/* SuperFastHash
 * ----------------
 * Paul Hsieh (http://www.azillionmonkeys.com/qed/hash.html)
 */
uint32_t SuperFastHash(const char * data, int len) {
  uint32_t hash = len, tmp;
  int rem;
  
  if (len <= 0 || data == NULL) return 0;
  rem = len & 3;
  len >>= 2;

  /* Main loop */
  for (;len > 0; len--) {
    hash += get16bits (data);
    tmp = (get16bits (data + 2) << 11) ^ hash;
    hash = (hash << 16) ^ tmp;
    data += 2 * sizeof (uint16_t);
    hash += hash >> 11;
  }

  /* Handle end cases */
  switch (rem) {
    case 3: hash += get16bits (data);
      hash ^= hash << 16;
      hash ^= ((signed char)data[sizeof (uint16_t)]) << 18;
      hash += hash >> 11;
      break;
    case 2: hash += get16bits (data);
      hash ^= hash << 11;
      hash += hash >> 17;
      break;
    case 1: hash += (signed char)*data;
      hash ^= hash << 10;
      hash += hash >> 1;
  }
  /* Force "avalanching" of final 127 bits */
  hash ^= hash << 3;
  hash += hash >> 5;
  hash ^= hash << 4;
  hash += hash >> 17;
  hash ^= hash << 25;
  hash += hash >> 6;

  return hash;
}

/* djb2
 * ------------
 * http://www.cse.yorku.ca/~oz/hash.html
 */
uint32_t djb2(const char *str) {
	uint32_t hash = 5381;
	int c;
	
	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	
	return hash;
}

/* Jenkins one-at-a-time
 * ----------------------
 * https://en.wikipedia.org/wiki/Jenkins_hash_function
 */

uint32_t jenkins_one_at_a_time_hash(const char *data, int len) {
	int i = 0;
  	uint32_t hash = 0;
	while (i != len) {
		hash += data[i++];
   	 	hash += hash << 10;
   		 hash ^= hash >> 6;
	 }
	 hash += hash << 3;
	 hash ^= hash >> 11;
	 hash += hash << 15;
	 return hash;
}