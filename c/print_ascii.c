#include "my_header.h"

int
main(int argc, char **argv)
{
	char *c;

	if (argc != 2) {
		printf("Bad arguments\n");
		printf("usage: ./a.out <char>\n");
		exit(-1);
	}
	c = argv[1];

	printf("ascii: %d\n", (int)c[0]);
	
	return (0);
}
