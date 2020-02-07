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
void enqueue(queue_head_t *head, void *data);
// remove an element from the queue
//
void *dequeue(queue_head_t *head);
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


/*
 * API For Stack
 *
 * - bool init(stack_t *)
 * - void push(item)
 * - item pop()
 * - int size()
 * - bool empty()
 * - uninit(stack_t *)
 */

// Init a stack
//
void stack_init(stack_head_t *head);
// Add a new element to the stack
//
void push(stack_head_t *head, void *data);
// remove an element from the stack
//
void *pop(stack_head_t *head);
// Returns the top element of the stack
// without removing it
//
void *peek(stack_head_t *head);
// return the size of the stack
//
int stack_size(stack_head_t *head);
// return is the stack is empty or not
//
bool stack_is_empty(stack_head_t *head);
// get memory for the new element in the stack
//
stack_t *stack_get_new_element(void *data);
// Un-init a stack
//
void stack_uninit(stack_head_t *head);

#endif // _QUEUE_H
