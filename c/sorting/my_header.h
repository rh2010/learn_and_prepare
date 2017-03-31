#include <stdio.h>
#include <stdlib.h>


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

// all the common helper function
void print_int_arr(int *arr, int size);
void swap_int(int *a, int *b);
