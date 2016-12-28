bloom.c
* [double hashing](http://citeseer.ist.psu.edu/viewdoc/download;jsessionid=4060353E67A356EF9528D2C57C064F5A?doi=10.1.1.152.579&rep=rep1&type=pdf):
hash_i(x, m) = (hash_a(x) + i*hash_b(x)) where i is an ordinal, m is the size of the bloom filter, and x is the value to be hashed
* optimal # of hash functions is - (ln p)/(ln 2) where p is the desired false positive probability


tests.c
* stress test by inserting ~1 mil entries and comparing the false positive rate