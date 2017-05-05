#include "../my_header.h"

typedef struct queue {
	void *data;
	queue_t *next
} queue_t;

typedef struct queue_head {
	int size;
	queue_t *head;
	queue_t *tail;
} queue_head_t;

// Init a queue
//
void queue_init(queue_head_t *head);
// Add a new element to the queue
//
void queue_enqueue(queue_head_t *head, void *data);
// remove an element from the queue
//
void *queue_remove(queue_head_t *head);
// return the size of the queue
//
int queue_size(queue_head_t *head);
// return is the queue is empty or not
//
bool queue_is_empty(queue_head_t *head);
// get memory for the new element in the queue
//
queue_t *queue_get_new_element(void *data);
