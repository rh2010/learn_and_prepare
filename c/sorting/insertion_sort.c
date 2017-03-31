#include "my_header.h"

#define ARRAY_SIZE 6

static void
insertion_sort_increasing(int *arr, int size)
{
	int i, j, key;

	printf("\n");
	for (j = 1; j < size; j++) {
		i = j - 1;
		key = arr[j];
		printf("\ni: %d, j: %d, key: %d\n", i, j, key);
		while ( i >= 0 && arr[i] > key) {
//			swap_int(&arr[i + 1], &arr[i]);
			SWAP(&arr[i + 1], &arr[i]);
			i--;
		}
		printf("Iteration %d, key: %d\n", j, key);
		print_int_arr(arr, ARRAY_SIZE);
	}
}

static void
insertion_sort_decreasing(int *arr, int size)
{
	int i, j, key, swaps;

	for (j = 1; j < size; j++) {
		i = j - 1;
		key = arr[j];
		swaps = 0;
		while ( i >= 0 && arr[i] < key) {
			SWAP(&arr[i], &arr[i + 1]);
			i--;
			++swaps;
		}
		printf("Iteration %d, key: %d, swaps: %d\n", j, key, swaps);
		print_int_arr(arr, ARRAY_SIZE);
	}
}

int
main(void)
{
	int i = 0;
	int orig_arr[ARRAY_SIZE] = {31, 41, 59, 26, 41, 58};

	int *arr = NULL;

	arr = (int *)malloc(ARRAY_SIZE);
	if (arr == NULL) {
		printf("Unable to allocate memory for the array\n");
		return (-1);
	}

	// init the array
	for (i = 0; i < ARRAY_SIZE; i++) {
		arr[i] = orig_arr[i];
	}

	printf("Original array\n");
	print_int_arr(orig_arr, ARRAY_SIZE);

//	insertion_sort_increasing(arr, ARRAY_SIZE);
	insertion_sort_decreasing(arr, ARRAY_SIZE);

	printf("Sorted array\n");
	print_int_arr(arr, ARRAY_SIZE);

	// all done, free the memory
	free(arr);

	return 0;
}
