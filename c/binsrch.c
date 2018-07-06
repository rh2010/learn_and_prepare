#include <stdio.h>
#include <stdlib.h>

/* 
 * Binary search 
 * It can be done only on a sorted array
 *
 */

int binsrch(int *arr, int len, int val)
{
	int start, end, mid;

	/* initialize the start and the end pointers */
	start = 0;
	end = len - 1;

	while (start <= end) {
		mid = (start + end) / 2;

		if (arr[mid] == val) {
			return mid;
		} else if (arr[mid] > val) {
			end = mid - 1;
		} else { // arr[mid] < val
			start = mid + 1;
		}
	}
	return -1;
}

int
rbins(int *arr, int start, int end, int val)
{
	int mid = (start + end)/2;

	if (arr[mid] == val) {
		return mid;
	}
	if (start == end) {
		printf("start: %d, end: %d\n", start, end);
		return -1;
	}
	if (val < arr[mid]) {
		return rbins(arr, start, mid-1, val);
	} 
	if (val > arr[mid]) {
		return rbins(arr, mid+1, end, val);
	}
}

int main(int argc, char **argv)
{
	int arr[100], val, len;
	int arg_idx = 0;
	int i, idx = 0;

	if (argc < 3) {
		printf("Too few arguments !!\n");
		exit(-1);
	}

	arg_idx++;
	val = atoi(argv[arg_idx++]);
	len = atoi(argv[arg_idx++]);

	for (i = 0; i < len; i++, arg_idx++) {
		arr[i] = atoi(argv[arg_idx]);
	}

	//idx = binsrch(arr, len, val);
	idx = rbins(arr, 0, len-1, val);

	if (idx == -1) {
		printf("%d not found in the array!!\n", val);
	} else {
		printf("%d found at index [%d] in the array!!\n", val, idx);
	}

	return 0;
}
