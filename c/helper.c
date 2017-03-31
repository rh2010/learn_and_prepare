#include "my_header.h"

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
print_int_arr_reverse(int *arr, int size)
{
	int i;

	printf("[%d]: ", size);
	for (i = size - 1; i >= 0; i--) {
		printf("%d", arr[i]);
		if (i > 0) {
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
