#include <../util.h>

/*
 * Implement
 * 	1) string length
 * 	2) string copy
 * 	3) string concatenate
 * 	4) strstr
 */
int
string_length(char *str)
{
	int i = 0;

	if (str == NULL) {
		printf("Bad string\n");
		return 0;
	}

	while(str[i++] != '\0');
		
	return i;
}

void
string_copy(char *src, char *dest, int length)
{
	printf("");
}

int
main(int argc, char** argv)
{
	int choice;
	char *str1, *str2, *res;

	str1 = str2 = res = NULL;

	while (1) {
		printf("1) strlen\n2) strcpy\n3) strcat\n4) strstr\n5) Exit\nChoice: ");
		scanf("%d", &choice);
		
		switch(choice) {
			case 1:
				str1 = NULL;
				printf("String: ");
				scanf("%s", str1);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			default:
				printf("Wrong Choice!\n");
				break;
		}

	}
}
