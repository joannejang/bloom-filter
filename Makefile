use_bloom: tests.c bloom.c
	cc -g -o use_bloom tests.c bloom.c

clean:
	rm use_bloom