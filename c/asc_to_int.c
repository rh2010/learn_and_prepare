#include <stdio.h>
#include <stdlib.h>

int asc_to_int(char *str)
{
	int num = 0;
	int i;

	for (i = 0; str[i] >= '0' && str[i] <= '9'; i++) {
		num = num * 10 + (str[i] - '0');
	}

	return num;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("usage: ./asc_to_int <a number>\n");
		exit(-1);
	}

	printf("The input number is %d\n", asc_to_int(argv[1]));
	return 0;
}
