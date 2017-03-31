#include "../my_header.h"

/*
 * 	1) string concatenation
 */
char*
string_cat(char *dest, char *src)
{
	int i = 0;
	int srclen;
	int dest_len = strlen(dest);
	srclen = strlen(src);

	if (src == NULL) {
		printf("Bad string\n");
		return NULL;
	}
	// check if overlapping
	if (dest > src && dest < (src+srclen)) {
		printf("Overlapping string\n");
		return NULL;
	}

	printf("Destlen: %d, src: %s\n", dest_len, src);

	while(src[i] != '\0')
		dest[dest_len+i] = src[i++];
	dest[dest_len+i] = '\0';

	printf("Dest: %s\n", dest);

	return (dest);
}

int
main(int argc, char** argv)
{
	char *str1;
	char res[40];
	char *str = " coding";

	if (argc < 2) {
		printf("./usage <a.out> <string>\n");
		exit(-1);
	}
	str1 = argv[1];
	printf("dest: %s\n", strncpy(res, str1, strlen(str1)));

	printf("Concatenated string is: %s\n", string_cat(str+2, str));
	printf("Concatenated string is: %s\n", string_cat(res, str));

	return (0);
}
