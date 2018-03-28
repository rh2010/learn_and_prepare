#include "../util.h"
#include <time.h>

/*
 * Implement a priority Queue as a Max-Heap.
 *
 * Implement as a Binary Heap (i.e. a complete binary tree)
 */

#define PARENT(i) ((i)/2)
#define LEFT_CHILD(i) ((2*(i)) + 1)
#define RIGHT_CHILD(i) ((2*(i)) + 2)

// structure for a heap
struct heap {
    int max_size; // max elements the heap can hold
    int size; // current size of the heap
    int *arr; // array to hold the elements in the heap
};

// heap methods.
struct heap *heap_init(struct heap *h, int max_size);
void heap_cleanup(struct heap *h);
int heap_insert(struct heap *h, int data);
int heap_get_max(struct heap *h);
int heap_peek_max(struct heap *h);
void heap_sift_up(struct heap *h, int index);
void heap_sift_down(struct heap *h, int index);
void heap_print(struct heap *h);
int heap_remove(struct heap *h, int index);
int heap_get_size(struct heap *h);
/*
 * Initialize the heap
 */
struct heap *
heap_init(struct heap *h, int max_size)
{
    assert(h != NULL);

    h->max_size = max_size;
    h->size = 0;

    // allocate memory for the heap data.
    h->arr = (int *)malloc((sizeof (int)) * max_size);
    if (h->arr == NULL) {
        printf("Unable to allocate memory for the heap data\n");
        exit(-1);
    }

    return NULL;
}

/*
 * Destroy the heap
 */
void
heap_cleanup(struct heap *h)
{
    assert(h != NULL);

    free(h->arr);
    h->size = h->max_size = 0;
}

/*
 * Insert an element in the heap
 *
 * return:
 *  0 for success
 *  -1 for failure
 */
int
heap_insert(struct heap *h, int data)
{
    assert(h != NULL);

    if (h->max_size == h->size) {
        printf("Error: Heap is already full\n");
        return -1;
    }

    printf("Adding %d\n", data);
    h->arr[h->size] = data;
    h->size += 1;
    assert(h->size <= h->max_size);
    heap_sift_up(h, h->size-1);

    return 0;
}

/*
 * Returns the max element from the heap
 * and also remove it from the heap.
 *
 * O (log n)
 */
int
heap_get_max(struct heap *h)
{
    int max;
    assert(h != NULL);

    if (h->size == 0) {
        printf("Error: Empty heap\n");
        return -1;
    }
    max = h->arr[0]; // element at the first position is always the max.

    // swap the max with the last element
    SWAP((h->arr), (h->arr+(h->size-1)));

    h->size = h->size - 1;
    heap_sift_down(h, 0);

    return max;
}

/*
 * Returns the max element from the heap but
 * does not remove it from the heap
 *
 * O (1)
 */
int
heap_peek_max(struct heap *h)
{
    int max;
    assert(h != NULL);

    if (h->size > 0) {
        max = h->arr[0];
    } else {
        printf("Empty Heap\n");
        max = -1;
    }
    return max;
}

/*
 * Siftup and element into correct position to maintain
 * the max heap property.
 *
 * O (log n)
 */
void
heap_sift_up(struct heap *h, int index)
{
    int parent_index;
    assert(h != NULL);
    assert(index < h->size);

    parent_index = PARENT(index);
    if (h->arr[parent_index] < h->arr[index]) {
        SWAP((h->arr + index), (h->arr + parent_index));
        heap_sift_up(h, parent_index);
    }
}

/*
 * Sift down an element into it's correct position
 * to maintain the heap property
 *
 * O (log n)
 */
void
heap_sift_down(struct heap *h, int index)
{
    int l, r, next;
    assert(h != NULL);
    assert(index <= h->size);

    next = index;

    l = LEFT_CHILD(index);
    if (l < h->size && h->arr[l] > h->arr[next]) {
        next = l;
    }

    r = RIGHT_CHILD(index);
    if (r < h->size && h->arr[r] > h->arr[next]) {
        next = r;
    }

    if (next != index) {
        SWAP((h->arr+next), (h->arr+index));
        heap_sift_down(h, next);
    }
}

/*
 * Dump the contents of the heap
 * For debugging
 */
void
heap_print(struct heap *h)
{
    int i;

    assert(h != NULL);

    printf("Heap Dump:\n");
    printf("\tMax Size: %d\n", h->max_size);
    printf("\tSize: %d\n", h->size);
    printf("\tData:\n\t");
    for (i=0; i < h->size; i++) {
        printf("%d ", h->arr[i]);
    }
    printf("\n");
}

/*
 * Remove an element from the heap. Adjust the heap
 * so the max heap property is maintained.
 */
int
heap_remove(struct heap *h, int index)
{
    int element;
    assert(h != NULL);
    assert(index < h->size);

    element = h->arr[index];
    h->arr[index] = INT_MAX;
    heap_sift_up(h, index);
    heap_get_max(h);

    return element;
}

/*
 * Returns the current size of the heap.
 */
int
heap_get_size(struct heap *h)
{
    assert(h != NULL);
    return h->size;
}

/*
 * Change the priority of the element at [index]
 * to [value]
 */
void
heap_change_priority(struct heap *h, int index, int value)
{
    int ele;
    assert(h != NULL);
    assert(index < h->size);

    ele = h->arr[index];
    h->arr[index] = value;

    if (value < ele) {
        heap_sift_down(h, index);
    } else {
        heap_sift_up(h, index);
    }
}

int
main(int argc, char** argv)
{
    int heap_size, range;
    int i;

    struct heap h;
    // create a heap of size [user input]
    if (argc != 3) {
        printf("Usage: ./heap <max size of heap> <range for element value> \n");
        return -1;
    }
    heap_size = atoi(argv[1]);
    range = atoi(argv[2]);

    // init the heap
    heap_init(&h, heap_size);

    // print the heap
    heap_print(&h);

    // randomly build the heap
    srand(time(NULL));

    for (i=0; i < heap_size; i++) {
        heap_insert(&h, rand()%range);
        printf("\tmax: %d\n", heap_peek_max(&h));
    }

    // print the heap.
    heap_print(&h);

    // change priority
    printf("Change priority:\n");
    printf("\tMax: %d\n", heap_peek_max(&h));
    heap_change_priority(&h, 0, 0);
    printf("\tMax: %d\n", heap_peek_max(&h));
    heap_change_priority(&h, h.size-1, heap_peek_max(&h)+range);
    printf("\tMax: %d\n", heap_peek_max(&h));

    // print the heap.
    heap_print(&h);

    // get the max elements
    printf("Max: %d\n", heap_get_max(&h));
    printf("Max: %d\n", heap_get_max(&h));
    printf("Max: %d\n", heap_get_max(&h));
    printf("Max: %d\n", heap_get_max(&h));

    // print the heap
    heap_print(&h);

    // remove an element from the heap.
    if (heap_get_size(&h) > 3) {
        printf("remove: %d\n", heap_remove(&h, heap_get_size(&h)-2));
    }

    // print the heap
    heap_print(&h);

    while(heap_get_size(&h) > 0) {
        printf("max: %d\n", heap_get_max(&h));
    }

    // print the heap
    heap_print(&h);

    // destroy the heap
    heap_cleanup(&h);

	return 0;
}
