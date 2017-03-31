#include <stdio.h>
#include <stdlib.h>

unsigned int
power(int a, unsigned int b)
{
	unsigned int res = 1;

	while (b > 0) {

		if (b & 1) {
			res *= a;
		}

		b = b >> 1;
		a *= a;
	}
	return res;
}

int main(int argc, char **argv)
{
	int a, b;
	a = b = 0;

	if (argc < 3) {
		printf("Bad Arg!!\n");
		exit(-1);
	}
	a = atoi(argv[1]);
	b = atoi(argv[2]);

	printf("%d to the power %d is %u\n", a, b, power(a, b));
}
