#include "../util.h"

/*
 * Asked in VMWare: Don't remember the question properly.
 * Hence, incomplete!
 *
 * TODO
 */

int
max_sum_subarray(int *arr, int size)
{

}
int
main(int argc, char **argv)
{
	int size;
	int i;
	int *arr;
	int sum = 0;

	if (argc <= 2) {
		printf("Too few arguments\n");
		printf("./a.out <array-size> <array of integers>\n");
		exit(-1);
	}

	size = atoi(argv[1]);

	// the total number of argument should be array-size + 2
	assert(argc == size+2);

	arr = (int *)malloc(sizeof(int) * size);
	if (arr == NULL) {
		printf("No memory for the array\n");
		exit(-1);
	}
	for(i = 0; i < size; i++) {
		arr[i] = atoi(argv[i+2]);
	}
	sum = max_sum_subarray(arr, size);
	printf("The longest sequence is: %d\n", sum);

	return(0);
}
