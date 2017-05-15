#include "../util.h"

/*
 * LIS - Longest Increasing Sub-sequence
 *
 * arr[0 ... n-1] => input array
 *
 * Let L(i) be the length of the LIS ending at index 'i', such that
 * arr[i] is the last element of the LIS.
 *
 * Then L(i) can be written as:
 *
 *  - L(i) = 1 + max(L(j)) where 0 < j < i and arr[j] < arr[i] or
 *  - L(i) = 1, if not such j exists.
 */
int find_lis(int *arr, int size)
{
	int *lis;
	int i, j;
	int max;

	// allocate memory for lis array of the same size as of the input array.
	lis = (int *)malloc(sizeof (int) * size);
	if (lis == NULL) {
		printf("Error, No Memory\n");
		exit(-1);
	}

	// initialize each element to 1.
	for (i = 0; i < size; i++) {
		lis[i] = 1; // init to 1
	}

	// lis[0] will always be '1'
	for (i = 1; i < size; i++) {

		// we will look at all elements leading upto 'i'
		for (j = 0; j < i; j++) {
			// if the current element 'i' being looked at is greater than 'j'
			// and the lis[i] is less than lis[j] + 1, update lis[i] with
			// lis[j] + 1, 1 for including ourselves.
			if ((arr[i] > arr[j]) && (lis[i] < lis[j] + 1)) {
				lis[i] = lis[j] + 1;
			}
		} // for 'j'
	} // for 'i'

	max = 0;
	// get the max from the lis array
	for (i = 0; i < size; i++) {
		if (max < lis[i]) {
			max = lis[i];
		}
	}
	free(lis);
	return max;
}

int
main(int argc, char **argv)
{
	int i;
	int size;
	int *arr;
	int max;

	if (argc < 3) {
		printf("Error, bad input\n");
		exit(-1);
	}
	size = atoi(argv[1]);

	arr = (int *)malloc(sizeof (int) * size);
	if (arr == NULL) {
		printf("Error, No Memory\n");
		exit(-1);
	}

	// fill the input array
	for (i=0; i < size; i++) {
		arr[i] = atoi(argv[i+2]);
	}

	max = find_lis(arr, size);
	printf("LIS: %d\n", max);

	free(arr);

	return (0);
}
