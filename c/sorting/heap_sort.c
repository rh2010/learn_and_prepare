#include "../util.h"
#include <time.h>

void
heap_sort(int *arr, int s)
{
    int size = s;

    for (i=0; i < size/2) {
        sift_down()
    }
}
/*
 * Implement heap sort.
 */
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
	range = atoi(argv[1]);

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

	heap_sort(arr, count);

	printf("Sorted array\n");
	print_int_arr(arr, count);

	// all done, free the memory
	free(arr);

	return 0;
}
