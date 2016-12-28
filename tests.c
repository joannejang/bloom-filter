#include "bloom.h"
#include "hash_functions.h"

#define INIT_SIZE 8

void apples_oranges() {
	bloom_filter* filter = create_filter(INIT_SIZE);
	assert(filter);
	
	printf("Should be false: ");
	printf(possibly_present(filter, "apple") ? "true\n" : "false\n");

	add_entry(filter, "apple");
	printf("Should be true: ");
	printf(possibly_present(filter, "apple") ? "true\n" : "false\n");

	printf("Should be false (but true is okay too): "); 
	printf(possibly_present(filter, "orange") ? "true\n" : "false\n");

	free_filter(filter);
}

/* 
 * Expected false positive rate with k = 3 (hashes) and 32 bits (m/n): 0.000717
 * k = 2, 32 bits: 0.00367
 * (http://pages.cs.wisc.edu/~cao/papers/summary-cache/node8.html)
 */
void stress_test_10k() {
	size_t size = 100000;
	bloom_filter* numbers = create_filter(size);
	assert(numbers);
	printf("New filter, about to add %zu entries...\n", size);
	for (int i = 0; i < size; i++) {
		char *str;
		asprintf(&str, "%i", i);
		add_entry(numbers, str);
		free(str);
	}
	printf("... done. %zu entries added. \n", numbers->size);

	int false_positive_count = 0;
	for (int j = 0; j < size; j++) {
		int random_int = rand() % (size*2);
		// considering false positive = when it says it's present but it's actually not
		if (random_int > 100000) {
			char *str_rand;
			asprintf(&str_rand, "%i", random_int);
			if (possibly_present(numbers, str_rand)) {
				false_positive_count++;
			}
			// free(str_rand);
		}
	}
	double rate = ((double) false_positive_count)/size;
	printf("False positive rate (should be somewhat close to 0.00367): %f\n", rate);
	free_filter(numbers);
}


int main() {
	printf("************ vvv basic ***************\n");
	apples_oranges();
	printf("************ less basic ****************\n");
	stress_test_10k();
	return 0;
}