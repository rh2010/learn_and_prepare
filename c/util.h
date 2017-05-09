#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h> // assert()
#include <limits.h>

#ifndef _UTIL_H_
#define _UTIL_H_
//#include <stdbool.h> // boolean

// All the helper MACROs go here.
/*
 * swap integers, pass integers as address (not by value)
 */
#define SWAP(x, y) {\
	int _tmp = *(x);\
	*(x) = *(y); \
	*(y) = _tmp; \
	}

// pass integers by value	
#define SWAP_FAST(x, y) {\
	*(x) = *(x) ^ *(y) \
	*(y) = *(x) ^ *(y) \
	*(x) = *(x) ^ *(y) \
	}

// mamimum of two integers
#define MAX(a, b) ( ((a) > (b)) ? (a) : (b))
// mimimum of two integers
#define MIN(a, b) ( ((a) < (b)) ? (a) : (b))

// Assert macro
#define ASSERT assert

// boolean
typedef enum {FALSE, TRUE} bool;

// all the common helper function
void print_int_arr(int *arr, int size);
void print_int_arr_reverse(int *arr, int size);
void swap_int(int *a, int *b);

#endif // __UTIL_H_
