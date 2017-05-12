#include "../util.h"

/*
 * Implement a program to inplace transpose a square matrix
 * of side n (i.e. N x N matrix).
 */
#define N 3

#define sswap(x, y) {\
	(x) = (x) ^ (y); \
	(y) = (x) ^ (y); \
	(x) = (x) ^ (y); \
	}

void
print_matrix(int arr[N][N], int size)
{
	int i, j;

	printf("Matrix:\n");

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

void
transpose(int a[N][N], int size)
{
	int i, j;
	int temp;

	printf("transpose\n");

	for (i = 0; i < size; i++) {
		for (j = i+1; j < size; j++) {
			//printf("J: %d\n", j);
			sswap(a[i][j], a[j][i]);
			//print_matrix(a, N);
			//printf("\n\n");
		}
	}

}

void
rotate_from_transpose(int a[N][N], int size)
{
	int i, j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size/2; j++) {
			sswap(a[i][j], a[i][size-j-1]);
		}
	}
}

int
main()
{
	int a[N][N] = {	{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	//int a[N][N] = {	{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

	print_matrix(a, N);
	transpose(a, N);
	printf("Matrix Transpose\n");
	print_matrix(a, N);
	rotate_from_transpose(a, N);
	printf("Matrix Rotate\n");
	print_matrix(a, N);
	return 0;
}
