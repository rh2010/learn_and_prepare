#include <stdio.h>
#include <stdlib.h>

/*
 *   INPUT:
 *      a => array of integer, sorted in increasing order (all values are unique)
 *      len => number of elements in array 'a' (could range from 0-10000)
 *      val => this is the value you wish to insert in the array 'a' so that , it remains sorted
 *
 *      OTUPUT:
 *       return index within array 'a', at which if we insert 'val', then the array remains sorted.

int find_insert_index(int *a, int len, int val)
{
	  /* implement this function (it is preferred that you use binary/O(log(n)) algorithm) */
/*
}


for e.g.
    a = {2, 4, 6, 8}, len = 4, val = 3  : should return 1
    a = {2, 4, 6, 8}, len = 4, val = 1  : should return 0
    a = {2, 4, 6, 8}, len = 4, val = 20  : should return 4

    Hint: Make sure all corner cases are taken care of
	  You need not insert value into the array, only return index into the array
 */

int find_insert_index(int *arr, int len, int val)
{
	int start, end, mid;

	start = 0;
	end = len - 1;

	while (start <= end) {
		mid = (start + end)/2;

		if (val < arr[mid]) {
			if ( ((mid-1) >= start ) && (val > arr[mid-1])) {
				return mid;
			}
			end = mid - 1;
		} else if (val > arr[mid]) {
			if ( ((mid+1) <= end ) && (val <= arr[mid + 1]) ) {
				return mid+1;
			}
			start = mid + 1;
		} else { // equal
			return mid;
		}
	}

	return ( (mid == start) ? start : len);
}

int main (int argc, char **argv)
{
	int len; /* length of the array */
	int val; /* value to be inserted */
	int *arr;
	int i = 0;

	if (argc < 4) {
		printf("Too few arguments\n");
		exit(0);
	}

	len = atoi(argv[1]);
	val = atoi(argv[2]);

	/* allocate the array */
	arr = (int *)malloc(len * sizeof(int));

	for (i = 0; i < len; i++) {
		arr[i] = atoi(argv[i + 3]);
	}

	/* print the input */
	printf("len = %d\nval = %d\narray: ", len, val);
	for (i = 0; i < len; i++) {
		printf("%d - ", arr[i]);
	}
	printf("\n");

	/* the answer */
	printf("The index is %d \n", find_insert_index(arr, len, val));

	return 0;
}
