#include "queue.h"

/*
 * A small program to validate queue.c and queue.h
 */

void
display_stack(stack_head_t *head)
{
	stack_t *temp;

	assert(head != NULL);
	printf("display_stack: ");
	// display the queue.
	//
	temp = head->head;

	printf("The stack has %d elements\n", stack_size(head));
	while (temp != NULL) {
		printf("%d ", *((int *)temp->data));
		temp = temp->next;
	}
	printf("\n");
}

void
display_queue(queue_head_t *head)
{
	queue_t *temp;

	assert(head != NULL);
	printf("display_queue: ");
	// display the queue.
	//
	temp = head->head;

	printf("The queue has %d elements\n", queue_size(head));
	while (temp != NULL) {
		printf("%d ", *((int *)temp->data));
		temp = temp->next;
	}
	printf("\n");
}

int
main(int argc, char **argv)
{
	int count;
	int i;
	int *arr, *ptr;
	int isStack;

	queue_head_t queue;
	stack_head_t stack;

	if (argc < 4) {
		printf("Too few arguments\n");
		printf("usage: ./a.out <0 | 1> <count of elements> <count # of elements>\n");
		printf("0 -> Queue, 1 -> stack\n");
		exit(-1);
	}
	isStack = atoi(argv[1]);

	count = atoi(argv[2]);

	if (argc != count+3) {
		printf("Too few arguments, given: %d, should be %d\n", argc, count+3);
		printf("usage: ./a.out <0 | 1> <count of elements> <count # of elements>\n");
		printf("0 -> Queue, 1 -> stack\n");
		exit(-1);
	}

	// allocate memory to hold the input array.
	arr = (int *)malloc(sizeof (int) * count);
	if (arr == NULL) {
		printf("No Memory\n");
		exit(-1);
	}

	if (!isStack) { // Run test for Queue
		// initialize the queue.
		//
		queue_init(&queue);

		display_queue(&queue);

		// fill in input array and build the queue.
		for (i = 0; i < count; i++) {
			arr[i] = atoi(argv[i+3]);

			enqueue(&queue, (void*)(&arr[i]));
		}
		printf("%d elements inserted into the queue\n", i);

		// verify that the queue has the said number of elements.
		assert(queue_size(&queue) == count);

		display_queue(&queue);

		// remove the first element.
		//
		ptr = (int *)dequeue(&queue);
		printf("The first element is %d\n", *ptr);

		display_queue(&queue);
		// remove the second element.
		//
		ptr = (int *)dequeue(&queue);
		printf("The second element is %d\n", *ptr);

		display_queue(&queue);
		// check if the queue is empty.
		//
		printf("Is the queue empty: %s\n", queue_is_empty(&queue) ? "YES" : "NO");

		// add the first element again.
		//
		printf("Adding the first element again\n");
		enqueue(&queue, (void *)arr);
		// check if the queue is empty.
		//
		printf("Is the queue empty: %s\n", queue_is_empty(&queue) ? "YES" : "NO");

		display_queue(&queue);

		// un-init the queue.
		//
		printf("Un-initing the queue\n");
		queue_uninit(&queue);

		display_queue(&queue);
	} else { // Run test for stack
		// initialize the stack.
		//
		stack_init(&stack);

		display_stack(&stack);

		// fill in input array and build the stack.
		for (i = 0; i < count; i++) {
			arr[i] = atoi(argv[i+3]);

			push(&stack, (void*)(&arr[i]));
		}
		printf("%d elements inserted into the stack\n", i);

		// verify that the stack has the said number of elements.
		assert(stack_size(&stack) == count);

		display_stack(&stack);

		// remove the first element.
		//
		ptr = (int *)pop(&stack);
		printf("The first element is %d\n", *ptr);

		display_stack(&stack);
		// remove the second element.
		//
		ptr = (int *)pop(&stack);
		printf("The second element is %d\n", *ptr);

		display_stack(&stack);
		// check if the stack is empty.
		//
		printf("Is the stack empty: %s\n", stack_is_empty(&stack) ? "YES" : "NO");

		// add the first element again.
		//
		printf("Adding the first element again\n");
		push(&stack, (void *)arr);
		// check if the queue is empty.
		//
		printf("Is the stack empty: %s\n", stack_is_empty(&stack) ? "YES" : "NO");

		display_stack(&stack);

		// un-init the stack.
		//
		printf("Un-initing the stack\n");
		stack_uninit(&stack);

		display_stack(&stack);
	}
	return (0);
}
