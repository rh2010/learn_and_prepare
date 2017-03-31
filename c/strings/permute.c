#include "../my_header.h"

void
swap(char *a, char *b)
{
	char tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
/*
 * 	1) print all permutations of a string
 */
void
permute(char *arr, int l, int r)
{
	int i;

	if ( l == r ) {
		printf("%s\n", arr);
	}
	for (i = l; i <= r; i++) {
		swap((arr+l), (arr+i));
		permute(arr, l+1, r);
		swap((arr+l), (arr+i));
	}
}

int
main(int argc, char** argv)
{
	char *str1;
	int len;

	if (argc < 2) {
		printf("./usage <a.out> <string>\n");
		exit(-1);
	}
	str1 = argv[1];
	len = strlen(str1);

	printf("Permutations for string %s are:\n", str1);
	permute(str1, 0, len-1);

	return (0);
}
