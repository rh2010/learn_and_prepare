#include "../util.h"

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
	int i, j;

	printf("\npartition: Enter\n");
	printf("partition: start: %d, end: %d\n", start, end);

	if (start >= end) {
		printf("partition: Exit: Done\n");
		// error
		return -1;
	}
	printf("partition: PIndex: %d, PValue: %d\n", end, arr[end]);

	p_index = end;
	p = arr[end];

	i = start;

	for (j = start; j <= end - 1; j++) {
		printf("partition: i: %d, j: %d\n", i, j);
		if (arr[j] <= p) {
			printf("partition: Swapping %d and %d\n", *(arr+i), *(arr+j));
			SWAP(arr+i, arr+j);
			i++;
		}
	}
	printf("partition: Final SWAP: %d and %d\n", *(arr+1), *(arr+end));
	SWAP((arr+i), (arr+end));

	// partition the array
	//
	printf("partition: PIndex: %d, PValue: %d\n", i+1, arr[i+1]);
	print_int_arr(arr, end-start+1);
	printf("partition: Exit\n\n");

	return i;
}
void
quick_sort(int *arr, int start, int end)
{
	int p_index;

	if (start >= end) {
		return;
	}

	p_index = partition(arr, start, end);

	// For debugging
	printf("partition index: %d\n", p_index);

	quick_sort(arr, start, p_index -1);
	quick_sort(arr, p_index + 1, end);
}

int
main(int argc, char **argv)
{
	int i = 0;
	int count;
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

	arr = (int *)malloc(sizeof (int) * count);
	if (arr == NULL) {
		printf("Unable to allocate memory for the array\n");
		return (-1);
	}

	// fill the array
	for (i = 0; i < count; i++) {
		arr[i] = atoi(argv[i+2]);
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
