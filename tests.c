#include "bloom.h"
#include "hash_functions.h"

#define INIT_SIZE 32

int main() {
	bloom_filter* filter = create_filter(INIT_SIZE);
	assert(!filter);
	printf("yay got a null ptr back <3\n");
	return 0;
}