#include "../util.h"

void
selection_sort(int *arr, int size)
{
	int i, j;
	int index;

	for (i=0; i<size-1; i++) {
		index = i;
		for(j=i; j<size; j++) {
			if (arr[j] < arr[index]) {
				index = j;
			}
		}
		if (i != index) {
			SWAP((arr+i), (arr+index));
		}
	}
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

	selection_sort(arr, count);

	printf("Sorted array\n");
	print_int_arr(arr, count);

	// all done, free the memory
	free(arr);

	return 0;
}
