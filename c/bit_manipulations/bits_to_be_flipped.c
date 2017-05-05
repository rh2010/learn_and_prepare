#include "../util.h"

int
bits_to_be_flipped(int num)
{
	unsigned int mask = 1<<31;
	int count = 0;

	while(mask) {
		if (num & mask) {
			count++;
		}
		mask = mask >> 1;
	}
	return count;
}

int
main(int argc, char **argv)
{
	int num1, num2;

	if (argc < 3) {
		printf("usage: ./a.out <integer> <integer>\n");
		exit(-1);
	}

	num1 = atoi(argv[1]);
	num2 = atoi(argv[2]);
	printf("Input: %d, %d\n", num1, num2);

	printf("Number of bits to be flipped from %d to %d is: %d\n", num1, num2, bits_to_be_flipped(num1 ^ num2));
}
