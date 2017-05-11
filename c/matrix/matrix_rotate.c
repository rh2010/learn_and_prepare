#include "../util.h"

/*
 * Implement a program to inplace right rotate (by 90 degrees) a square matrix
 * of side n (i.e. N x N matrix).
 */
#define N 4

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
right_rotate_90(int a[N][N], int size)
{
	int i, j;
	int temp;

	printf("right_rotate_90\n");

	for (i = 0; i < size/2; i++) {
		printf("i: %d\n", i);
		for (j = i; j < size -i -1; j++) {
			printf("J: %d\n", j);

			temp 			= a[i][j];
			a[i][j] 		= a[N-j-1][i];
			a[N-j-1][i] 	= a[N-i-1][N-j-1];
			a[N-i-1][N-j-1] = a[j][N-i-1];
			a[j][N-i-1] = temp;

			print_matrix(a, N);
			printf("\n\n");
		}
	}

}

int
main()
{
	//int a[N][N] = {	{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	int a[N][N] = {	{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

	print_matrix(a, N);
	right_rotate_90(a, N);
	return 0;
}
