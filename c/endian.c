#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_little_endian(void)
{
	int var = 1;
	char *cptr = NULL;
	cptr = (char *)&var;

	printf("Addr:Var [%p:%x],[%p:%x],[%p:%x],[%p:%x]\n", &cptr[0], cptr[0], &cptr[1], cptr[1], &cptr[2], cptr[2], &cptr[3], cptr[3]);
	return (cptr[0] == 1);
}

int main(void)
{
	if (is_little_endian()) {
		printf("Little Endian \n");
	} else {
		printf("Big Endian \n");
	}

	return 0;
}
