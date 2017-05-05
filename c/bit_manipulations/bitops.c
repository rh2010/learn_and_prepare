#include "../util.h"

#define POSITIVE 1 // positive sign
#define NEGATIVE 0 // negative sign
#define CHAR_BITS 8 // number of bits in a char

int
main(int argc, char **argv)
{
	int num;
	bool sign;
	bool f;
	unsigned int mask = 0xf; // 111
	unsigned int w;
	unsigned int tmp, tmp1;

	if (argc < 2) {
		printf("usage: ./a.out <integer>\n");
		exit(-1);
	}
	num = atoi(argv[1]);
	sign = num >> (sizeof(int) * CHAR_BITS - 1);
	printf("Sign is %d\n", sign);

	w = num;

	printf("Input is: %d\n", w);

	f = TRUE;
	tmp = -f ^ w;
	tmp1 = tmp & mask;
	w ^= (-f ^ w) & mask;
	printf("Output is: %d\n", w);

	// reset
	w = num;
	f = FALSE;
	tmp = -f ^ w;
	tmp1 = tmp & mask;
	w ^= (-f ^ w) & mask;
	printf("Output is: %d\n", w);

	return (0);
}
