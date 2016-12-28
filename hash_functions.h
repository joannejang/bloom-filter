#ifndef _HASH_FUNCTIONS_H
#define _HASH_FUNCTIONS_H

#include <stdlib.h> // like, everything
#include <assert.h> // unit tests
#include <stdio.h> // print statements
#include <stdint.h> // int in hash functions

uint32_t hash_SuperFastHash(const char *data, int len); // these might need to be unsigned char

uint32_t hash_djb2(const char *str);

uint32_t hash_jenkins_one_at_a_time(const char *data, int len);

#endif