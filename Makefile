test_bloom: tests.c bloom.c hash_functions.c
	cc -g -o test_bloom tests.c bloom.c hash_functions.c

clean:
	rm test_bloom