#include "queue.h"

/*
 * A small program to validate queue.c and queue.h
 */
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

	queue_head_t queue;

	if (argc < 3) {
		printf("Too few arguments\n");
		printf("usage: ./a.out <count of elements> <count # of elements>\n");
		exit(-1);
	}
	count = atoi(argv[1]);

	if (argc != count+2) {
		printf("Too few arguments, given: %d, should be %d\n", argc, count+2);
		printf("usage: ./a.out <count of elements> <count # of elements>\n");
		exit(-1);
	}

	// allocate memory to hold the input array.
	arr = (int *)malloc(sizeof (int) * count);
	if (arr == NULL) {
		printf("No Memory\n");
		exit(-1);
	}

	// initialize the queue.
	//
	queue_init(&queue);

	display_queue(&queue);

	// fill in input array and build the queue.
	for (i = 0; i < count; i++) {
		arr[i] = atoi(argv[i+2]);

		queue_enqueue(&queue, (void*)(&arr[i]));
	}
	printf("%d elements inserted into the queue\n", i);

	// verify that the queue has the said number of elements.
	assert(queue_size(&queue) == count);

	display_queue(&queue);

	// remove the first element.
	//
	ptr = (int *)queue_remove(&queue);
	printf("The first element is %d\n", *ptr);

	display_queue(&queue);
	// remove the second element.
	//
	ptr = (int *)queue_remove(&queue);
	printf("The second element is %d\n", *ptr);

	display_queue(&queue);
	// check if the queue is empty.
	//
	printf("Is the queue empty: %s\n", queue_is_empty(&queue) ? "YES" : "NO");

	// add the first element again.
	//
	printf("Adding the first element again\n");
	queue_enqueue(&queue, (void *)arr);
	// check if the queue is empty.
	//
	printf("Is the queue empty: %s\n", queue_is_empty(&queue) ? "YES" : "NO");

	display_queue(&queue);
	// un-init the queue.
	//
	printf("Un-initing the queue\n");
	queue_uninit(&queue);

	display_queue(&queue);
	return (0);
}
