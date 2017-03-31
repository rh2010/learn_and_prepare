#include <stdio.h>
#include <stdlib.h>

int string_len(char *str)
{
	int i = 0;

	while(str[i] != '\0')
		i++;
	printf("Length [%d]\n", i);
	return i;
}

char *lower(char *str)
{
	int len = 0;
	int i;

	printf("Lower ");

	len = string_len(str);

	for (i = 0; i < len; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] + ('a' - 'A');
		}
	}
	printf(" [%s] \n", str);
	return str;
}

char *upper(char *str)
{
	int len = 0;
	int i;

	printf("Upper ");

	len = string_len(str);

	for (i = 0; i < len; i++) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			str[i] = str[i] - ('a' - 'A');
		}
	}
	printf(" [%s] \n", str);
	return str;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("usage: ./lower <string>\n");
		exit(-1);
	}

	printf("Input [%s], LowerCase [%s], UpperCase [%s]\n", (char*)argv[1], lower(argv[1]), upper(argv[1]));

	return 0;
}
