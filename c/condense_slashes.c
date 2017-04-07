#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * If there are multiple contiguous slashes in a string, condense them into
 * a single slash.
 */
void
condense_slashes(char *str)
{
	int len, i, wptr;
	int flag = 0;

	if (str == NULL) {
		printf("NULL String\n");
		return;
	}

	len = strlen(str);

	for (i = 0, wptr = 0; i < len; i++) {
		/*
		 * After the first time, every subsequent contigous occurrance of a '/'
		 * we should not not take any action.
		 */
		if (flag && str[i] == '/') {
			continue;
		}
		/*
		 * After a '/' when ever a '/' is not seen, reset the flag.
		 */
		if (flag) {
			flag = 0;
			
		} else {
			/*
			 * The first time a '/' is seen set the flag.
			 */
			if (str[i] == '/') {
				flag = 1;
			}
		}	
		str[wptr] = str[i];
		wptr++;
	}
	str[wptr] = '\0';
}

int
main(int argc, char **argv)
{
	char *str = NULL;

	if (argc < 2) {
		printf("usage: ./a.out <string>\n");
		exit(-1);
	}
	str = argv[1];
	printf("Input:\n%s\n", str);
	condense_slashes(str);
	printf("Input:\n%s\n", str);
	return (0);
}
