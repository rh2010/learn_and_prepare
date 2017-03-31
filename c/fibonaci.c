#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void fibonaci(int num)
{
	int i;
	int fib, pfib;

	fib = pfib = 0;

	for (i = 1; i <= num; i++) {
		if (i == 1) {
			// do nothing
		} else if (i == 2) {
			fib = 1;
		} else {
			fib = fib + pfib;
			pfib = fib - pfib;
		}

		printf("%d ", fib);
	}
}

void print_num(int pfib, int fib, bool both)
{
	if (both) {
		printf("%d %d ", pfib, fib);
	} else {
		printf("%d ", pfib);
	}
}

void fibonaci2(int num)
{
	int i;
	int fib, pfib;

	pfib = 0;
	fib = 1;

	for (i = 2; i < num; i += 2) {
		print_num(pfib, fib, true);

		pfib = pfib + fib;
		fib = pfib + fib;
	}

	if (i == num) {
		print_num(pfib, fib, true);
	} else {
		print_num(pfib, fib, false);
	}
}

int
recursive_fibonaci(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	return recursive_fibonaci(n - 1) + recursive_fibonaci(n - 2);
}

int main(int argc, char **argv)
{
	int num;
	int i = 0;

	if (argc != 2) {
		printf("usage: ./fibonaci <number of elements in the series> \n");
		exit(-1);
	}

	num = atoi(argv[1]);

	printf("The fibonaci series is: ");
	fibonaci(num);
	printf("\n");

	printf("The fibonaci series is (optimized): ");
	fibonaci2(num);
	printf("\n");

	for (i = 0; i < num ; i++) {
		printf("%d ", recursive_fibonaci(i));
	}
	printf("\n");
	return 0;
}
