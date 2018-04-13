#include "../util.h"

#define ARRAY_SIZE 4

int
merge(int *arr, int left, int mid, int right)
{
	int i, j, k;
	int llen, rlen;
	int count;
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
	count = 0;
	k = left;

	printf("llen: %d, rlen: %d: left: %d, mid: %d: right: %d\n", llen, rlen, left, mid, right);
	print_int_arr(larr, llen);
	print_int_arr(rarr, rlen);

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
			printf("Adding: %d\n", (llen-i));
			count += llen - i;
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

	print_int_arr((int *)(arr+left), (right-left+1));
	return count;
}

int
mergesort(int *arr, int left, int right)
{
	int mid, count;

	count = 0;
	
	if (left < right) {
		mid = left + (right - left)/2;

		count = mergesort(arr, left, mid);
//		printf("1 count: %d\n", count);
		count += mergesort(arr, mid+1, right);
//		printf("2 count: %d\n", count);

		count += merge(arr, left, mid, right);
//		printf("2 count: %d\n", count);
	}
	return count;
}

int
main(int argc, char **argv)
{
	int i = 0;
	int count;
	int *arr = NULL;
	//int orig_arr[ARRAY_SIZE] = {31, 41, 59, 26, 41, 58};
	//int orig_arr[ARRAY_SIZE] = {8, 4, 2, 1};
	//count = ARRAY_SIZE

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

	// init the array
	//for (i = 0; i < ARRAY_SIZE; i++) {
	//	arr[i] = orig_arr[i];
	//}

	printf("Original array\n");
	print_int_arr(arr, count);

//	insertion_sort_increasing(arr, ARRAY_SIZE);
	printf("Inversions are %d\n", mergesort(arr, 0, (count - 1)));

	printf("Sorted array\n");
	print_int_arr(arr, count);

	// all done, free the memory
	free(arr);

	return 0;
}
