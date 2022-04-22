#include "../util.h"
#include <time.h>

/*
 * 2nd version of quick sort
 */
int
partition(int *arr, int s, int e)
{
	int i, j, p;

	if (s >= e) {
		return -1;
	}
	// i partition index
	// j till where the partition is done
	p = arr[s]; // let's use the first element as the pivot element to partition around
	i = s;

	for (j=s+1; j<=e;j++) {
		if (arr[j] <= p) {
			i++;
			if (i != j) {
				SWAP((arr+i), (arr+j));
			}
		}
	}
	SWAP((arr+s), (arr+i));

	return i;
}

void
quick(int *arr, int s, int e)
{
	int p_index;
	printf("qs: s: %d, e: %d\n", s, e);
	print_int_arr_pos(arr, s, e-s+1);
	if  (s >= e) {
		printf("\n");
		return;
	}
	p_index = partition(arr, s, e);

	printf("Partition Index: [%d] %d\n", p_index, arr[p_index]);
	print_int_arr_pos(arr, s, e-s+1);
	printf("\n");

	quick(arr, s, p_index-1);
	quick(arr, p_index+1, e);
}

int
main(int argc, char **argv)
{
	int i = 0;
	int count, range;
	int *arr = NULL;

	if (argc != 3) {
		printf("usage: ./a.out <count of elements> <range >\n");
		exit(-1);
	}

	count = atoi(argv[1]);
	range = atoi(argv[2]);

	arr = (int *)malloc(sizeof (int) * count);
	if (arr == NULL) {
		printf("Unable to allocate memory for the array\n");
		return (-1);
	}

	// randomly fill the array
    srand(time(NULL));

	for (i = 0; i < count; i++) {
		arr[i] = rand() % range;
	}

	printf("Input array\n");
	print_int_arr(arr, count);

	quick(arr, 0, count-1);

	printf("Sorted array\n");
	print_int_arr(arr, count);

	// all done, free the memory
	free(arr);

	return 0;
}
