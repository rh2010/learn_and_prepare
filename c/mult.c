#include <stdio.h>
#include <stdlib.h>

/*
 * Multiply two integers without using the * operator.
 */
int multiply(int a, int b)
{
	int num = 0;
	int i = 1;

	while (b != 0) {
		printf("%d) In loop: a [%d], b [%d], num [%d]\n", i, a, b, num);
		if ((b & 1) != 0) {
			num += a;
		printf("%d) In if cond: a [%d], b [%d], num [%d]\n", i, a, b, num);
		}
		b = b >> 1;
		a = a << 1;
		printf("%d) a [%d], b [%d], num [%d]\n", i, a, b, num);
		i++;
		printf("\n");
	}

	printf("Final: a [%d], b [%d], num [%d]\n", a, b, num);
	return num;
}

int main(int argc, char **argv)
{
	int a, b;

	if (argc != 3) {
		printf("usage: ./mult <int> <int>\n");
		exit(-1);
	}

	a = atoi(argv[1]);
	b = atoi(argv[2]);

	printf("[%d] * [%d] = [%d]\n", a, b, multiply(a, b));

	return 0;
}
