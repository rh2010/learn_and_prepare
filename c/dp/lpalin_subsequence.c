#include "../util.h"

/*
 * Longest Palindromic Sub-Sequence
 */
int
lps(char *a, int s, int e)
{
	// case 1: if there is only single character
	if (s == e) {
		return 1;
	}
	// case 2: if there are two characters and they both are same
	if ( s+1 == e && a[s] == a[e]) {
		return 2;
	}
	// case 3: if the first and the last characters match
	// and the string is more than 2 characters.
	if (a[s] == a[e]) {
		return lps(a, s+1, e-1) + 2;
	}

	// case 4: if the first and the last characters do not match
	return MAX(lps(a, s+1, e), lps(a, s, e-1));
}

int
lpsdp(char *str, int size)
{
	int i, j;
	int l; // length of the sub-string
	int lps[size][size];

	// each character is a palindrome of size 1
	for (i = 0; i<size; i++) {
		lps[i][i] = 1;
	}

	for(l = 2; l <= size; l++) {
		for (i=0; i<size-l+1; i++) {
			j = i+l-1;

			if (str[i] == str[j] && l == 2) {
				lps[i][j] = 2;
			} else if (str[i] == str[j]) {
				lps[i][j] = lps[i+1][j-1] + 2;
			} else {
				lps[i][j] = MAX(lps[i][j-1], lps[i+1][j]);
			}
		}
	}

	return lps[0][size-1];
}

int
main(int argc, char **argv)
{
	int i;
	int sizex;
	char *x;

	if (argc != 2) {
		printf("Error, bad input!\n");
		exit(-1);
	}

	x = argv[1];

	sizex = strlen(x);

	printf("Longest Palindromic Sub-Sequence is %d\n", lps(x, 0, sizex-1));
	printf("Longest Palindromic Sub-Sequence (dp) is %d\n", lpsdp(x, sizex));

	return (0);
}
