#include "../util.h"

/*
 * Implement Kadane's algorithm for long consecutive sum
 *
 * The algorithm doesn't work if all the integers in the array are -ve
 */
int ls(int *arr, int size)
{
	int i;
	int max_so_far;
	int curr_so_far;

	max_so_far = arr[0];
	curr_so_far = arr[0];

	for (i = 1; i < size; i++) {
		curr_so_far = MAX(arr[i], (arr[i] + curr_so_far));
		max_so_far = MAX(max_so_far, curr_so_far);
	}
	return max_so_far;
}

int
longest_sum(int *arr, int start, int end)
{
	int i, sum, max_sum;
	int first_index, last_index;

	sum = 0;
	max_sum = INT_MIN;
	first_index = last_index = 0;

	for (i = start; i <= end; i++) {
		sum += arr[i];

		if (sum > max_sum) {
			max_sum = sum;
			last_index = i;
		}
		if (sum < 0) {
			sum = 0;
			first_index = i + 1;
		}
	}
	printf("The max sub-array is from : %d - %d\n", first_index, last_index);

	return (max_sum);
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
	sum = longest_sum(arr, 0, size-1);
	printf("The longest sum is: %d\n", sum);

	printf("The longest sum ls (handle all -ve numbers): %d\n", ls(arr, size));

	return(0);
}
