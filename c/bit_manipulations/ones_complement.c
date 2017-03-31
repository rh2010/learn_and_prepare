#include <stdio.h>
#include <stdlib.h>

void
print_in_binary(int x)
{
	unsigned int z = 2147483648;
	char c;
	int print = 0;
	printf("Binary representation of %d is: ", x);

	while(z) {
		c = (((z&x)==z)?'1':'0');

		if (print ==0 && c == '1') {
			print = 1;
		}

		if (print) {
			printf("%c", c);
		}
		z >>= 1;
	}
	printf("\n");

	return;
}

void
count_bits(int x, int *bit_count, int *bits_set)
{
	unsigned int z = 2147483648; // 2^31
	int count = 0;
	int set_bits = 0;
	int count_flag = 0;

	while(z) {
		if ((z&x)) {
			set_bits++;
			if (count_flag == 0) {
				// toggle the count_flag
				count_flag = 1;
			}
		}
		if (count_flag) {
			count++;
		}
		z >>= 1;
	}
	if (bit_count != NULL) {
		*bit_count = count;
	}

	if (bits_set != NULL) {
		*bits_set = set_bits;
	}

	return;
}

int
main(int argc, char **argv)
{
	int i;
	int res; // store the one's complement in this
	int twosres; // store the two's complement in this.
	int num_bits = 0;
	int num_bits_set = 0;
	int mask;

	if (argc < 2) {
		printf("usage: ./a.out <an integer>\n");
		exit(-1);
	}

	i = atoi(argv[1]);

	printf("Input: %d\n", i);
	print_in_binary(i);
	count_bits(i, &num_bits, &num_bits_set);

	printf("Number of bits in %d is: %d\n", i, num_bits);
	printf("Number of bits set in %d is: %d\n", i, num_bits_set);

	// perform one's complement.
	res = ~i;
	//mask = (1U << num_bits) - 1;
	//res = i ^ mask;
	print_in_binary(res);

	// perform two's complement
	twosres = res + 1;
	print_in_binary(twosres);
	return (0);
}
