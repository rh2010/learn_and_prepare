#include "../util.h"


void
print_int_arr(int *arr, int size)
{
	int i;

	printf("[%d]: ", size);
	for (i = 0; i < size; i++) {
		printf("%d", arr[i]);
		if (i < (size - 1)) {
			printf(" - ");
		}
	}
	printf("\n");
}

void
swap_int(int *a, int *b)
{
	int x, y;

	x = *a;
	y = *b;

	printf("Before swap, a: %d, b: %d\n", x, y);
	x = x ^ y;
	y = x ^ y;
	x = x ^ y;
	printf("After swap, a: %d, b: %d\n", x, y);
}
