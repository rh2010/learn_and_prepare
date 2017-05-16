#include "../util.h"

/*
 * Longest Palindromic Substring
 */
int
lps(char *s)
{

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

	printf("Longest Palindromic Substring is %d\n", lps(x));

	return (0);
}
