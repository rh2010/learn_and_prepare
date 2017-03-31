#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SWAP(x, y) \
	(x) = (x) ^ (y); \
	(y) = (x) ^ (y); \
	(x) = (x) ^ (y); \
	
//#define SWAP(x, y) \
//	x = x ^ y; \
//	y = x ^ y; \
//	x = x ^ y; \

void swap_1(int *a, int *b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

void rev_arr(int *arr, int size)
{
	int i;

	for (i = 0; i < (size)/2; i++) {

		SWAP( (arr[i]), (arr[(size-1) - i]) );
//		SWAP( arr[i], arr[b] );
//		SWAP( arr[i], arr[(size-1)-i] );


//		swap_1( &(arr[i]), &(arr[(size-1) - i]) );
//		swap_1();
	}

}

int main(int argc, char **argv)
{
	int size;
	int *arr;
	int i;

	if (argc < 3) {
		printf("usage: ./arr_rev <size> <array elements> \n");
		exit(-1);
	}

	// get the size
	size = atoi(argv[1]);

	// allocate space for the array
	arr = (int *)malloc(sizeof(int) * size);
	if (arr == NULL) {
		printf("No memory !!\n");
		exit(-1);
	}

	// get the array
	for (i = 0; i < size; i++) {
		arr[i] = atoi(argv[i+2]);
	}

	// printf input
	printf("Size: [%d], Array [ ", size);
	for (i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("] \n");

	rev_arr(arr, size);

	// printf input
	printf("Size: [%d], Array [ ", size);
	for (i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("] \n");
	return 0;
}
