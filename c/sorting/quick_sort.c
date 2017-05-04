#include "my_header.h"

/*
 * Program to implement Quick-Sort sorting algorithm.
 */

/*
 * Given the arr, the start index and the end index
 * find the index on which to partition on and then
 * partition the array such that all the elements to
 * the left of the partition element are less than it
 * and all the elements to the right of it are greater
 * than it.
 */
int
partition(int *arr, int start, int end)
{
	int p, p_index;

	if (start >= end) {
		// error
		return -1;
	}

	p = arr[end];
	p_index = end;

	// partition the array
	//
}

void
quick_sort(int *arr, int start, int end)
{
	int p_index;

	if (start >= end) {
		return;
	}

	p_index = partition(arr, start, end);

	quick_sort(arr, start, p_index -1);
	quick_sort(arr, p_index + 1, end);
}

int
main(void)
{
	int i = 0;
	int size;

	int orig_arr[ARRAY_SIZE] = {8, 4, 2, 1};

	int *arr = NULL;

	if (argc < 3) {
		printf("usage: ./a.out <count of elements> <count number of integers>\n");
		exit(-1);
	}

	count = atoi(argv[1]);

	if (argc != count + 2) {
		printf("Wrong number of arguments\n");
		printf("usage: ./a.out <count of elements> <count number of integers>\n");
		exit(-1);
	}

	arr = (int *)malloc(i(sizeof int) * count);
	if (arr == NULL) {
		printf("Unable to allocate memory for the array\n");
		return (-1);
	}

	// init the array
	for (i = 0; i < count; i++) {
		arr[i] = orig_arr[i];
	}

	printf("Input array\n");
	print_int_arr(arr, count);

	quick_sort(arr, 0, count - 1);

	printf("Sorted array\n");
	print_int_arr(arr, count);

	// all done, free the memory
	free(arr);

	return 0;
}
