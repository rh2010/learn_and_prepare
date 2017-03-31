#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int len = 0;
	char *str = NULL;
	char *res = NULL;

	int start_ptr, end_ptr, loop_control;
	int i, j;

	start_ptr =  0;
	end_ptr = len;
	i = j = 0;

	if (argc < 2) {
		printf("Bad Arg!\n");
		exit(-1);
	}

	str = argv[1];

	if (str == NULL) {
		printf("Bad Input!\n");
		exit(-1);
	}

	len = strlen(str);

	res = (char *)malloc(3*len);
	if (res == NULL) {
		printf("Unable to allocated memory for the result, bailing out!\n");
		exit(-1);
	}
	memset(res, 0, (3*len));

	i = 0;

	// remove the leading white space
	while (i < len) {
		if (str[i++] == ' ') {
			start_ptr++;
		} else {
			break;
		}
	}

	if (start_ptr == len) {
		printf("Bad Input\n");
		exit(-1);
	}

	i = end_ptr = len-1;

	// adjust for the trailing white-spaces
	while (i > 0) {
		if (str[i--] == ' ') {
			end_ptr--;
		} else {
			break;
		}
	}

	j = 0;
	for (i = start_ptr; i <= end_ptr; i++) {
		if (str[i] == ' ') {
			res[j++] = '%';
			res[j++] = '2';
			res[j++] = '0';
		} else {
			res[j++] = str[i];
		}
	}
	res[j] = '\0'; // just to be safe

	printf("Input string: %s\n", str);
	printf("Result: \n %s\n", res);

	free(res);
	return (0);
}

