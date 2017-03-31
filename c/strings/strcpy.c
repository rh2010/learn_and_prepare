#include "../my_header.h"

/*
 * 	1) string copy
 */
char *
string_copy(char *src, char *dest)
{
	int i = 0;
	int srclen;

	if (src == NULL) {
		printf("Bad string\n");
	}
	srclen = strlen(src);

	// destlen should be at least srclen + 1
	while(src[i] != '\0') {
		dest[i] = src[i++];
	}

	dest[i] = '\0';
	return (dest);
}

int
main(int argc, char** argv)
{
	char *str1;
	int len;
	char *dest;

	if (argc < 2) {
		printf("./usage <a.out> <string>\n");
		exit(-1);
	}
	str1 = argv[1];
	len = strlen(str1);

	dest = (char*)malloc(len+1);
	if (dest == NULL) {
		printf("Could not allocate memeory for dest\n");
		exit(-1);
	}

	printf("Copied string is: %s\n", string_copy(str1, dest));
	free(dest);

	return (0);
}
