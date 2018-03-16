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
left_rotate(int a[N][N], int size)
{
	int i, j, temp;

	for (i=0; i<size/2; i++) {
		for(j=i; j < size - i - 1; j++) {
			temp = a[i][j];
			a[i][j] = a[j][size-i-1];
			a[j][size-i-1] = a[size-i-1][size-j-1];
			a[size-i-1][size-j-1] = a[size-j-1][i];
			a[size-j-1][i] = temp;
		}
	}
}

void
right_rotate_90(int a[N][N], int size)
{
	int i, j;
	int temp;

	for (i = 0; i < size/2; i++) {
		for (j = i; j < size -i -1; j++) {
			temp 			= a[i][j];
			a[i][j] 		= a[N-j-1][i];
			a[N-j-1][i] 	= a[N-i-1][N-j-1];
			a[N-i-1][N-j-1] = a[j][N-i-1];
			a[j][N-i-1] = temp;
		}
	}

}

int
main()
{
	//int a[N][N] = {	{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	int a[N][N] = {	{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

	print_matrix(a, N);

	printf("Right Rotate:\n");
	right_rotate_90(a, N);
	print_matrix(a, N);

	printf("Left Rotate:\n");
	left_rotate(a, N);
	print_matrix(a, N);
	return 0;
}
