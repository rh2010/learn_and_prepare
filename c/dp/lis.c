#include "../util.h"

/*
 * LIS - Longest Increasing Sub-sequence
 */
int find_lis(int *arr, int size)
{
	int *lis;
	int i, j;
	int max;

	lis = (int *)malloc(sizeof (int) * size);
	if (lis == NULL) {
		printf("Error, No Memory\n");
		exit(-1);
	}

	for (i = 0; i < size; i++) {
		lis[i] = 1; // init to 1
	}

	for (i = 1; i < size; i++) {
		for (j = 0; j < i; j++) {
			if ((arr[i] > arr[j]) && (lis[i] < lis[j] + 1)) {
				lis[i] = lis[j] + 1;
			}
		}
	}

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
