#include "queue.h"

/* Queue */
// Init a queue
//
void
queue_init(queue_head_t *head)
{
	assert(head != NULL);

	head->size = 0;
	head->head = NULL;
}

// Init a queue
//
void
queue_uninit(queue_head_t *head)
{
	queue_t *temp;
	queue_t *element;

	assert(head != NULL);

	if (head->size == 0) {
		// nothing to be done
		return;
	}

	// free all the elements hanging off the queue.
	temp = head->head;

	assert(temp != NULL);

	while (temp != NULL) {
		element = temp;
		temp = temp->next;

		free(element);
	}
	queue_init(head);
}

// Add a new element to the queue
//
void
enqueue(queue_head_t *head, void *data)
{
	queue_t *temp;
	queue_t *new;

	assert(head != NULL);

	temp = head->head;

	new = queue_get_new_element(data);
	if (new == NULL) {
		printf("Error: No memory for new element\n");
		return;
	}
	new->next = head->head;
	head->head = new;
	head->size++;
}

// remove an element from the queue
//
void *
dequeue(queue_head_t *head)
{
	queue_t *prev;
	queue_t *temp;
	void *data;

	assert(head != NULL);

	data = NULL;

	if (!head->size) {
		printf("Empty Queue\n");
		return NULL;
	}

	prev = NULL;
	temp = head->head;

	while(temp->next != NULL) {
		prev = temp;
		temp = temp->next;
	}

	if (prev == NULL) {
		// if only one element is present in the list
		assert(head->size == 1);
		data = temp->data;
		free(temp);
		queue_init(head);
	} else {
		// if more than one element in the list
		assert(head->size > 1);

		prev->next = NULL;
		data = temp->data;
		free(temp);
		head->size--;

		assert(head->size);
	}
	return data;
}

// return the size of the queue
//
int
queue_size(queue_head_t *head)
{
	return head->size;
}

// return is the queue is empty or not
//
bool
queue_is_empty(queue_head_t *head)
{
	return (head->size == 0);
}

// get memory for the new element in the queue
//
queue_t *
queue_get_new_element(void *data)
{
	queue_t *new;

	new = (queue_t*)malloc(sizeof (queue_t));
	if (new == NULL) {
		printf("queue_get_new_element: Error - No Memory\n");
		return NULL;
	}
	new->next = NULL;
	new->data = data;

	return new;
}


/* Stack */

// Init a stack
//
void
stack_init(stack_head_t *head)
{
	queue_init((queue_head_t *)head);
}

// Add a new element to the stack
//
void
push(stack_head_t *head, void *data)
{
	enqueue((queue_head_t *)head, data);
}

// remove an element from the stack
//
void *
pop(stack_head_t *head)
{
	stack_t *temp;
	void *data;

	assert(head != NULL);

	temp = head->head;

	if (temp == NULL) {
		// empty stack
		printf("Empty Stack\n");
		return NULL;
	}

	// remove the first node.
	// make the head point to what ever the first not is pointing to.
	head->head = temp->next;
	data = temp->data;
	head->size--;

	free(temp);

	return data;
}

// return the size of the stack
//
int
stack_size(stack_head_t *head)
{
	return head->size;
}

// return is the stack is empty or not
//
bool
stack_is_empty(stack_head_t *head)
{
	return (head->size == 0);
}

// get memory for the new element in the stack
//
stack_t *
stack_get_new_element(void *data)
{
	return (stack_t *)queue_get_new_element(data);
}

// Un-init a stack
//
void
stack_uninit(stack_head_t *head)
{
	queue_uninit((queue_head_t *)head);
}

