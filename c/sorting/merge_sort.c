#include "../util.h"

#define ARRAY_SIZE 4

void
merge(int *arr, int left, int mid, int right)
{
	int i, j, k;
	int llen, rlen;
	int larr[mid - left + 1];
	int rarr[right - mid];

	llen = mid - left + 1;
	rlen = right - mid;

	// copy data in the left / right sub-array from the original array.
	for (i = 0; i < llen; i++) {
		larr[i] = arr[left + i];
	}
	for (i = 0; i < rlen; i++) {
		rarr[i] = arr[mid + 1 + i];
	}
	i = 0;
	j = 0;
	k = left;

	/*
	 * while there is data to be processed in both the sub-arrays, compare the
	 * first element in each sub-array and put the smaller on in the main
	 * array and move on.
	 *
	 * the left and the right sub-arrays are themselves sorted.
	 */
	while ( (i < llen) && (j < rlen) ) {
		if (larr[i] <= rarr[j]) {
			arr[k] = larr[i];
			i++;
		} else {
			arr[k] = rarr[j];
			j++;
		}
		k++;
	}

	while(i < llen){
		arr[k] = larr[i];
		i++;
		k++;
	}

	while(j < rlen){
		arr[k] = rarr[j];
		j++;
		k++;
	}
}

int
mergesort(int *arr, int left, int right)
{
	int mid;

	
	if (left < right) {
		mid = left + (right - left)/2;

		mergesort(arr, left, mid);
		mergesort(arr, mid+1, right);

		merge(arr, left, mid, right);
	}
}

int
main(void)
{
	int i = 0;
	//int orig_arr[ARRAY_SIZE] = {31, 41, 59, 26, 41, 58};
	int orig_arr[ARRAY_SIZE] = {8, 4, 2, 1};

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
	printf("Inversions are %d\n", mergesort(arr, 0, (ARRAY_SIZE - 1)));

	printf("Sorted array\n");
	print_int_arr(arr, ARRAY_SIZE);

	// all done, free the memory
	free(arr);

	return 0;
}
