#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
	int num;
	int revd = 0;
	int digit;

	if (argc != 2) {
		printf("usage: ./rev_digits <number>\n");
		exit(-1);
	}

	num = atoi(argv[1]);

	printf("input number [%d] ", num);
	while (num) {
		digit = num % 10;
		revd = (revd * 10) + digit;
		num /= 10;
	}
	printf("w/ digitis reversed [%d]\n", revd);

	return 0;
}
