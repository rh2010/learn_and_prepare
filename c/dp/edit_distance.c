#include "../util.h"

#define MIN_3(a, b, c) ( MIN((MIN((a), (b))), (c)) )

int **
get_result_buffer(int row, int col)
{
	int **res;
	int i;

	res = (int **)malloc(sizeof(int*) * row);

	for (i=0; i<row; i++) {
		res[i] = (int *)malloc(sizeof(int)*col);
	}

	return res;
}

void
dump_result(int **res, int row, int col)
{
	int i, j;

	printf("Matrix:\n");
	for (i=0; i<row; i++) {
		for (j=0; j<col; j++) {
			printf("%d ", res[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int
edit_distance(char *str1, char *str2)
{
	int len1, len2;
	int i, j;
	int **result;

	if (str1 == NULL) {
		len1 = 0;
	} else {
		len1 = strlen(str1);
		printf("str1: %s, ", str1);
	}
	printf("len1: %d\n", len1);

	if (str2 == NULL) {
		len2 = 0;
	} else {
		len2 = strlen(str2);
		printf("str2: %s, ", str2);
	}
	printf("len2: %d\n", len2);

	if (len1+len2 == 0) {
		return 0;
	}

	// the result array - with row / column 1 + length of the string.
	result = get_result_buffer(len1+1, len2+1);

	//int result[len1+1][len2+1];

	// initialize for string1 - row
	// keep the column fixed at 0
	for (i = 0; i <= len1; i++) {
		result[i][0] = i;
	}
	//dump_result(result, len1+1, len2+1);
	// initialize for string2 - column
	// keep the row fixed at 0
	for (i = 0; i <= len2; i++) {
		result[0][i] = i;
	}
	//dump_result(result, len1+1, len2+1);

	// fill the result matrix.
	for (i = 1; i <= len1; i++ ) {
		for (j = 1; j <= len2; j++) {
			// if at this position the alphabet is same
			// then take the value from the diagonal.
			if (str1[i-1] == str2[j-1]) {
				result[i][j] = result[i-1][j-1];
			} else {
				// take the min of diagonal, upper and left element.
				result[i][j] = MIN_3(result[i-1][j-1],
									 result[i][j-1],
									 result[i-1][j]) + 1;
			}
		}
	}
	//dump_result(result, len1+1, len2+1);

	// result is the last element in the diagonal.
	return result[len1][len2];
}

int
main(int argc, char **argv)
{
	char *str1;
	char *str2;

	if (argc != 3) {
		printf("./usage: a.out <string1> <string1>\n");
		return (-1);
	}

	printf("Edit distance: %d\n", edit_distance(argv[1], argv[2]));

	return(0);
}
