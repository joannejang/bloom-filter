#include "bloom.h"

#define INIT_SIZE 16

int main() {
	bloom_filter* filter = create_filter(INIT_SIZE);
	assert(!filter);
	return 0;
}