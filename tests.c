#define _GNU_SOURCE

#include "bloom.h"
#include "hash_functions.h"

#define INIT_SIZE 32

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

#define MAXINT_CHARS 12

char* itoa(int n) {
  char* buf = malloc(MAXINT_CHARS * sizeof(char));
  snprintf(buf, MAXINT_CHARS, "%d", n);
  return buf;
}

void gen_random_string(char **s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; ++i) {
        (*s)[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    (*s)[len] = '\0';
}

/* 
 * Expected false positive rate with k = 3 (hashes)
 * (http://pages.cs.wisc.edu/~cao/papers/summary-cache/node8.html)
 */
void stress_test_10k_ints() {
	size_t size = 10000;
	bloom_filter* numbers = create_filter(size);
	assert(numbers);

	for (int i = 0; i < size; i++) { // n = 10000
		char *str = itoa(i);
		add_entry(numbers, str);
		free(str);
	}

	int arr[size*2];
	int false_positive_count = 0;
	for (int j = 0; j < size; j++) {
		int random_int = rand() % (size*2);
		while (arr[random_int] == 1) {
			random_int = rand() % (size*2);
		}
		arr[random_int] = 1;

		// considering false positive = when it says it's present but it's actually not
		if (random_int >= 10000) {
			char *str_rand = itoa(random_int);
			if (possibly_present(numbers, str_rand)) {
				// printf("%s\n", str_rand);
				false_positive_count++;
			}
			free(str_rand);
		}
	}
	double rate = ((double) false_positive_count)/size;
	printf("False positive rate: %f\n", rate);

	free_filter(numbers);
}

// Commenting this out until I find a more elegant way to test this (that is, w/o a bash + python script :( )
void stress_test_strings() {
	size_t size = 10000;
	bloom_filter* strings = create_filter(size); // m = 320000
	assert(strings);
	// printf("New filter, about to add %zu entries...\n", size);

	for (int i = 0; i < size; i++) { // n = 10000
		int len = (rand() % 6) + 1;
		char *str = malloc(len + 1);
		gen_random_string(&str, len);
		printf("%s\n", str);
		add_entry(strings, str);
		free(str);
	}
	//printf("... done. %zu entries added. \n", numbers->size);
	printf(" ------------------------------------------------ ");
	for (int i = 0; i < size*2; i++) { // n = 10000
		int len = (rand() % 6) + 1;
		char *str = malloc(len + 1);
		gen_random_string(&str, len);
		if (possibly_present(strings, str)) {
			printf("%s\n", str);
		}
		free(str);
	}
	free_filter(strings);
}

int main() {
	printf("************ vvv basic ***************\n");
	apples_oranges();
	printf("************ less basic ****************\n");
	stress_test_10k_ints();
	// stress_test_strings
	return 0;
}
