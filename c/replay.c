#include <stdio.h>

int main (int argc, char **argv)
{
	int i;
	char c;

	for (i = 0; i < 5; i++) {
		scanf("%d ", &c);
		printf("%d ", i);
	}
	printf("\n");

	return 0;
}
