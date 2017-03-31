#include <stdio.h>
#include <stdlib.h>

int factorial(int n)
{
	if (n == 0) {
		return 1;
	}

	return (n * factorial(n-1));
}

int
ifactorial(int n)
{
	int i = 0;
	int res = 1;

	for (i = 0; i <= n; i++) {
		if (i == 0) {
			res = 1;
		} else {
			res *= i;
		}
	}
	return res;
}

int main(int argc, char **argv)
{
	int n;

	if (argc < 2) {
		printf("usage: ./factorial <number>\n");
		exit(-1);
	}

	n = atoi(argv[1]);

	printf("Factoral of %d is %d\n", n, factorial(n));
	printf("Factoral of %d is %d\n", n, ifactorial(n));
	return 0;
}
