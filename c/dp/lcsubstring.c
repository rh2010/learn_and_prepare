#include "../util.h"

int
mmax(int a, int b)
{
	return (a > b) ? a : b;
}

/*
 * LCS - Longest Common Sub-string
 *
 * TODO: To be done.
 * Examples:
 * LCS for input Sequences “ABCDGH” and “AEDFHR” is “ADH” of length 3.
 * LCS for input Sequences “AGGTAB” and “GXTXAYB” is “GTAB” of length 4.
 *
 * Naive solution:
 * 	- Generate all possible sub-sequences of both given sequences and find the
 * 	longest matching subsequence.
 * 	- Time complexity: Exponential
 *
 */
int
lcs_naive(char *x, char *y, int sizex, int sizey)
{
	if (sizex == 0 || sizey == 0) {
		return 0;
	}

	if (x[sizex-1] == y[sizey-1]) {
		return 1 + lcs_naive(x, y, sizex-1, sizey-1);
	} else {
		return mmax(lcs_naive(x, y, sizex-1, sizey),
					lcs_naive(x, y, sizex, sizey-1));
	}
}

/*
 * Dynamic programming solution:
 *
 * - Table building solution
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

	if (argc != 3) {
		printf("Error, bad input\n");
		exit(-1);
	}
	x = argv[1];
	y = argv[2];

	sizex = strlen(x);
	sizey = strlen(y);

	printf("lcs_naive: %d\n", lcs_naive(x, y, sizex, sizey));
	printf("LCS: %d\n", find_lcs(x, y, sizex, sizey));

	return (0);
}
