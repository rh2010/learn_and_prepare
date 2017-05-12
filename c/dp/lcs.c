#include "../util.h"

int
mmax(int a, int b)
{
	return (a > b) ? a : b;
}

/*
 * LCS - Longest Common Sub-sequence
 */
int find_lcs(char *x, char *y, int m, int n)
{
	int lcs[m+1][n+1];
	int i, j;

	printf("Input: X[%d]: %s, Y[%d]: %s", m, x, n, y);

	// print lcs
	//for (i = 0; i <= m; i++) {
	//	for (j = 0; j <= n; j++) {
	//		lcs[i][j] = 0;
	//		printf("%d ", lcs[i][j]);
	//	}
	//	printf("\n");
	//}

	for (i = 0; i <= m; i++) {
		for (j = 0; j <= n; j++) {
			// TODO: Fill this
			if (i == 0 || j == 0) {
				lcs[i][j] = 0;
			} else if (x[i-1] == y[j-1]) {
				lcs[i][j] = lcs[i-1][j-1] + 1;
			} else {
				lcs[i][j] = mmax(lcs[i-1][j], lcs[i][j-1]);
			}
		}
	}

	// print lcs
	//printf("LCS: Post processing\n");
	//for (i = 0; i <= m; i++) {
	//	for (j = 0; j <= n; j++) {
	//		printf("%d ", lcs[i][j]);
	//	}
	//	printf("\n");
	//}

	return lcs[m][n];
}

int
main(int argc, char **argv)
{
	int i;
	int sizex;
	int sizey;
	char *x;
	char *y;
	int max;

	if (argc != 3) {
		printf("Error, bad input\n");
		exit(-1);
	}
	x = argv[1];
	y = argv[2];

	sizex = strlen(x);
	sizey = strlen(y);

	max = find_lcs(x, y, sizex, sizey);
	printf("LCS: %d\n", max);

	return (0);
}
