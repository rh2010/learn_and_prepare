#include "../my_header.h"

/*
 * 	1) string length
 */
int
string_length(char *str)
{
	int i = 0;

	if (str == NULL) {
		printf("Bad string\n");
		return 0;
	}

	while(str[i] != '\0')
		i++;
		
	return (i);
}

int
main(int argc, char** argv)
{
	char *str1;

	if (argc < 2) {
		printf("./usage <a.out> <string>\n");
		exit(-1);
	}
	str1 = argv[1];

	printf("Length of string %s is %d, %ld \n", str1, string_length(str1), strlen(str1));
	
	return (0);
}
