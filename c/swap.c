#include <stdio.h>
#include <stdlib.h>

#define SWAP(x, y) \
	x = x ^ y; \
	y = x ^ y; \
	x = x ^ y; \


void swap_tmp(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap_1(int *a, int *b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

void swap_2(int *a, int *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

int main(int argc, char **argv)
{
	int a, aa, b, bb;

	if (argc != 3) {
		printf("Not enough arguments !!\n");
		exit(-1);
	}

	a = aa = b = bb = 0;

	a = aa = atoi(argv[1]);
	b = bb = atoi(argv[2]);

	printf("Input is a [%d], b [%d]\n", aa, bb);

	/* swap using tmp variable */
	swap_tmp(&aa, &bb);
	printf("swap_tmp: a [%d], b [%d]\n", aa, bb);
	aa = a;
	bb = b;

	/* swap without using tmp variable - approach 1 */
	swap_1(&aa, &bb);
	printf("swap_1: a [%d], b [%d]\n", aa, bb);
	aa = a;
	bb = b;


	/* swap without using tmp variable - approach 2 */
	swap_2(&aa, &bb);
	printf("swap_2: a [%d], b [%d]\n", aa, bb);
	aa = a;
	bb = b;

	SWAP(aa, bb);
	printf("SWAP: a [%d], b [%d]\n", aa, bb);

	return 0;
}
