#include "../my_header.h"

#define BITS	32

unsigned int
left_rotate(int num, int count)
{
	return (num << count) | (num >> (BITS - count));
}

unsigned int
right_rotate(int num, int count)
{
	return (num >> count) | (num << (BITS - count));
}

int
main(int argc, char** argv)
{
	int num = 0;

	if (argc < 2) {
		printf("./usage <a.out> <a +ve integer>\n");
		exit(-1);
	}

	num = atoi(argv[1]);

	// left rotate num
	printf("Left rotate: %u\n", left_rotate(num, 4));

	// right rotate num
	printf("Right rotate: %u\n", right_rotate(num, 2));
	return (0);
}
