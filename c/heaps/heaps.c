#include "../util.h"

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
    return -1;
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
    assert(h != NULL);
    return 0;
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
    assert(h != NULL);

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
    assert(h != NULL);

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
    assert(h != NULL);
    return 0;
}

int
main(int argc, char** argv)
{
    int heap_size, range;
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
    //
    // print the heap
    heap_print(&h);
    //
    // randomly fill in the heap with size elements
    //
    // print the heap.
    heap_print(&h);
    //
    // get the max elements
    //
    // print the heap
    heap_print(&h);

    // remove an element from the heap.
    heap_remove(&h, 3);

    // destroy the heap
    heap_cleanup(&h);

	return 0;
}
