#include "bloom.h"
#include "hash_functions.h"

#define INIT_SIZE 32

int main() {
	bloom_filter* filter = create_filter(INIT_SIZE);
	assert(filter);
	
	printf("Should be false: ");
	printf(possibly_present(filter, "apple") ? "true\n" : "false\n");

	add_entry(filter, "apple");
	printf("Could be true (but false is okay too): ");
	printf(possibly_present(filter, "apple") ? "true\n" : "false\n");

	free_filter(filter);
	return 0;
}