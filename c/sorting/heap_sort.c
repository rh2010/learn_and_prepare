#include "../util.h"
#include <time.h>

#define PARENT(i) ((i)/2)
#define LEFT_CHILD(i) ((2*(i)) + 1)
#define RIGHT_CHILD(i) ((2*(i)) + 2)

/*
 * sift down
 */
void
sift_down(int *arr, int index, int size)
{
    int l, r, next;

    assert(arr != NULL);
    assert(index <= size);

    next = index;

    l = LEFT_CHILD(index);
    if (l < size && arr[l] > arr[next]) {
        next = l;
    }
    r = RIGHT_CHILD(index);
    if (r < size && arr[r] > arr[next]) {
        next = r;
    }

    if (index != next) {
        SWAP((arr+index), (arr+next));
        sift_down(arr, next, size);
    }
}

/*
 * From a given array of integers in random order,
 * but, a max heap out of it ... in place.
 */
void
heapify(int *arr, int s)
{
    int i, size = s;

    for (i=size/2; i >= 0; i--) {
        sift_down(arr, i, s);
    }
}

void
heap_sort(int *arr, int size)
{
    int i;

    assert(arr != NULL);

    // build a max-heap out of the array
    heapify(arr, size);

    int running_size = size;
    while ((running_size - 1) > 0) {
        // swap the first and the last element in the array
        // the first element is the max element.
        // so, place the first element in the last position.
        SWAP((arr), (arr+running_size-1));
        running_size = running_size - 1;
        // bring the next highest max element of the array in the
        // first position.
        sift_down(arr, 0, running_size);
    }
}

/*
 * Implement heap sort.
 */
int
main(int argc, char **argv)
{
	int i = 0;
	int count, range;
	int *arr = NULL;

	if (argc != 3) {
		printf("usage: ./a.out <count of elements> <range >\n");
		exit(-1);
	}

	count = atoi(argv[1]);
	range = atoi(argv[2]);

	arr = (int *)malloc(sizeof (int) * count);
	if (arr == NULL) {
		printf("Unable to allocate memory for the array\n");
		return (-1);
	}

	// randomly fill the array
    srand(time(NULL));

	for (i = 0; i < count; i++) {
		arr[i] = rand() % range;
	}

	printf("Input array\n");
	print_int_arr(arr, count);

	heap_sort(arr, count);

	printf("Sorted array\n");
	print_int_arr(arr, count);

	// all done, free the memory
	free(arr);

	return 0;
}
