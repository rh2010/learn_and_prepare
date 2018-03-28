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
struct heap *heap_init(int max_size);
void heap_cleanup(void);
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
heap_init(int max_size)
{
    return NULL;
}

/*
 * Destroy the heap
 */
void
heap_cleanup(void)
{

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
    return 0;
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

}

/*
 * Dump the contents of the heap
 * For debugging
 */
void
heap_print(struct heap *h)
{

}

/*
 * Remove an element from the heap. Adjust the heap
 * so the max heap property is maintained.
 */
int
heap_remove(struct heap *h, int index)
{
    return 0;
}

int
main(int argc, char** argv)
{
	return 0;
}
