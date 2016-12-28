test_bloom: tests.c bloom.c
	cc -g -o test_bloom tests.c bloom.c

clean:
	rm test_bloom