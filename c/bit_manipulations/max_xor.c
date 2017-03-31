#include "../my_header.h"

int maxXor(int *arr, int size)
{
	int i, j;
	int xor;
	int res = 0;

	for (i=0; i < size; i++) {
		xor = 0;
		printf("i: %d, xor: %d\n", i, xor);

		for (j=i; j<size; j++) {
			xor = xor ^ arr[j];
			printf("xor: %d, j: %d\n", xor, j);
			res = MAX(res, xor);
		}
	}
	return res;
}

int
main(int argc, char **argv)
{
	int size;
	int arr[] = {8, 1, 2, 12};
	
	printf("Array: [8, 1, 2, 12]\n");
	size = sizeof arr / sizeof (arr[0]);
	printf("MaxXor is: %d\n", maxXor(arr, size));

	return(0);
}
