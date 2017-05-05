#include "../my_header.h"

#ifndef _QUEUE_H_
#define _QUEUE_H_


typedef struct queue {
	void *data;
	struct queue *next;
} queue_t;

typedef struct queue_head {
	int size;
	struct queue *head;
	struct queue *tail;
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

#endif // _QUEUE_H
