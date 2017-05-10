#include "../util.h"

void
swap(char *a, char *b)
{
	char tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int
fact(int num)
{
	int i;
	int fact;

	i = 0;
	fact = 0;

	for (i = 0; i <= num; i++) {
		if (i == 0) {
			fact = 1;
		} else {
			fact *= i;
		}
	} // end for loop

	return fact;
}

void
ipermute(char *arr)
{
	int length, factorial;
	int i, j, k, m;
	char *perm;

	length = (int)strlen(arr);
	factorial = fact(length);

	k = 0;
	m = 0;

	// allocate space for perm string
	perm = (char *)malloc(length + 1);
	if (perm == NULL) {
		printf("Not enough space for the perm array\n");
		exit(-1);
	}

	for (i = 0; i < factorial; ) {

		// set the perm string to the original string
		memcpy(perm, arr, length + 1);

		/*
		 * Fix the first position and iterate (n-1) characters
		 * upto (n - 1)!
		 * 'k' is the number of iterations for the first character.
		 */
		k = 0;
		while (k != factorial / length) {
			j = 1;

			/*
			 * swap the 'j'th value till it reaches the end position. 
			 */
			while (j != length -1) {
				/*
				 * Print the current permutation.
				 */
				printf("%s\n", perm);

				swap(perm+j, perm+j+1);

				j++;
				k++;
				i++;
			} // while for j
		} // while for k

		/*
		 * move the next character to be fixed in arr.
		 */
		m++;

		swap(arr, arr+m);
	} // for loop

}

/*
 * 	1) print all permutations of a string recursively
 */
void
permute(char *arr, int l, int r)
{
	int i;

	if ( l == r ) {
		printf("%s\n", arr);
		return;
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

	printf("Permutations (recursive) for string %s are:\n", str1);
	permute(str1, 0, len-1);
	printf("Permutations (iterative) for string %s are:\n", str1);
	ipermute(str1);

	return (0);
}
