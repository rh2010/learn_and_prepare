#include <stdio.h>
#include <stdlib.h>

int **dpalloc(int row, int col)
{
	int **dp;
	int i;

	dp = (int **)malloc(sizeof(int *) * row);

	for (i = 0; i < row; i++) {
		dp[i] = (int *)malloc(sizeof(int) * col);
	}

	return dp;
}

void dpinit(int **arr, int row, int col)
{
	int i, j;

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			arr[i][j] = 0;
		}
	}
}

void dpprint(int **arr, int row, int col)
{
	int i, j;

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	int row, col;
	int **arr;

	if (argc != 3) {
		printf("usage: ./2darr <row> <col>\n");
		exit(-1);
	}

	row = atoi(argv[1]);
	col = atoi(argv[2]);

	arr = dpalloc(row, col);

	dpprint(arr, row, col);
	dpinit(arr, row, col);
	printf("\n **** \n");
	dpprint(arr, row, col);

	return 0;
}
