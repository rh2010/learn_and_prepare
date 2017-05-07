#include "../util.h"

#ifndef _QUEUE_H_
#define _QUEUE_H_


typedef struct queue {
	void *data;
	struct queue *next;
} queue_t;

typedef struct queue_head {
	int size;
	struct queue *head;
} queue_head_t;

typedef queue_t stack_t;
typedef queue_head_t stack_head_t;

/* API For Queue*/
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
// Un-init a queue
//
void queue_uninit(queue_head_t *head);


/* API For Stack*/
// Init a stack
//
void stack_init(stack_head_t *head);
// Add a new element to the queue
//
void stack_enqueue(stack_head_t *head, void *data);
// remove an element from the queue
//
void *stack_remove(stack_head_t *head);
// return the size of the queue
//
int stack_size(stack_head_t *head);
// return is the queue is empty or not
//
bool stack_is_empty(stack_head_t *head);
// get memory for the new element in the queue
//
stack_t *stack_get_new_element(void *data);
// Un-init a queue
//
void stack_uninit(stack_head_t *head);

#endif // _QUEUE_H
