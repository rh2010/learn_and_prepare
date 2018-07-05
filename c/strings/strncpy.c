#include "../util.h"

/*
 * 	1) string 'n' copy
 */
char *
string_n_copy(char *dest, char *src, int len)
{
	int i = 0;
	int srclen;

	if (src == NULL) {
		printf("Bad string\n");
		return (NULL);
	}
	if (dest == NULL) {
		printf("Bad destinatio string\n");
		return (NULL);
	}

	printf("src: %s, srclen: %ld, destlen: %d\n", src, strlen(src), len);

	// destlen should be at least srclen + 1
	for (i = 0; i < len && src[i] != '\0'; i++) {
		dest[i] = src[i];
//		printf("copying [%d] %c\n", i, dest[i]);
	}
//	printf("dest: %s\n", dest);

	for(; i < len; i++) {
		dest[i] = '\0';
//		printf("Null at %d\n", i);
	}
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

	dest = (char*)malloc(len+10);
	if (dest == NULL) {
		printf("Could not allocate memeory for dest\n");
		exit(-1);
	}

	printf("Copied string is: %s\n", string_n_copy(dest, str1, (len+5)));
	free(dest);

	return (0);
}
