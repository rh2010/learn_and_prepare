#include <stdio.h>
#include <stdlib.h>

/* 
 * Input#
 * arr: the array
 * start: starting index
 * end: ending index
 * len: Total length of the initial array
 * 	
 * Return#
 *  -1 if not found
 *  If found the minumum number, the Index in the array
 */

int
minsearch(int *arr, int start, int end)
{
	int mid;
	int idx = 0;

	printf("Start: %d, End: %d, Len: %d\n", start, end, end+1);

	while (start <= end) {
		mid = (start + end)/2;

		printf("start: %d, end: %d, mid: %d, mid+1: %d\n",
				start, end, mid, mid+1);
		printf("arr[start]: %d, arr[end]: %d, arr[mid]: %d, arr[mid+1]: %d\n",
				arr[start], arr[end], arr[mid], arr[mid+1]);

		if (arr[mid] > arr[mid+1]) {
			idx = mid + 1;
			printf("Found!\n");
			break;
		}

		if (arr[start] < arr[mid]) {
			// all sorted in this half
			// discrepancy in other half
			start = mid + 1;
			printf("First half sorted\n");
		} else {
			// second half is sorted
			// min should be in the first half
			end = mid;
			printf("Second half sorted\n");
		}
	}
	return idx;
}

int main(int argc, char **argv)
{
	int arr[100], len;
	int arg_idx = 0;
	int i, idx = 0;

	if (argc < 3) {
		printf("Too few arguments !!\n");
		exit(-1);
	}

	arg_idx++;
	len = atoi(argv[arg_idx++]);

	for (i = 0; i < len; i++, arg_idx++) {
		arr[i] = atoi(argv[arg_idx]);
	}

	//idx = minsrch(arr, 0, len-1, len);
	idx = minsearch(arr, 0, len-1);

	if (idx == -1) {
		printf("Bug!!\n");
	} else {
		printf("Index [%d] in the array!!\n", idx);
	}
	return 0;
}
