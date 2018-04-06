#include "../util.h"

/*
 * Macros for moving between parent and children
 * in a rooted complete binary tree represented by
 * an array.
 */
#define PARENT(i) ((i-1)/2)
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
