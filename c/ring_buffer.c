#include <stdio.h>
#include <stdlib.h>

/*
 * Implement a ring buffer
 *
 *  - insert in the head.
 *  - remove from the tail.
 */
#define RBUF_SIZE 10

typedef struct ring_buffer {
	int buffer[RBUF_SIZE];
	// lock - place holder for a lock
	int head;
	int tail;
	int size;
} ring_buffer;

struct ring_buffer rbuf;

void
ring_buffer_dump(ring_buffer *rbuf)
{
	int i = 0;

	printf("Ring Buffer Debug\n");
	if (rbuf == NULL) {
		printf("NULL ring buffer\n");
		return;
	}
	
	printf("Size: %d\nStart: %d\nEnd: %d\n", RBUF_SIZE, rbuf->head, rbuf->tail);
	printf("full buffer:\n");

	for (i = 0; i < RBUF_SIZE; i++) {
		printf(": %d :", rbuf->buffer[i]);
	}
	printf("\n");
	
	printf("filled buffer\n");
	for (i = rbuf->tail; i != rbuf->head ; i = (i + 1)%RBUF_SIZE) {
		printf(": %d :", rbuf->buffer[i]);
	}
	printf("\n");
}

int
ring_buffer_insert(ring_buffer *rbuf, int data)
{
	// is full
	if ((rbuf->head - rbuf->tail + RBUF_SIZE ) % RBUF_SIZE == (RBUF_SIZE - 1)) {
		return (-1);
	}
	rbuf->buffer[rbuf->head] = data;
	rbuf->head = (rbuf->head + 1) % RBUF_SIZE;

	return (0);
}

int
ring_buffer_remove(ring_buffer *rbuf)
{
	int data;
	// is empty
	if (rbuf->head == rbuf->tail) {
		return (-1);
	}
	data = rbuf->buffer[rbuf->tail];
	rbuf->buffer[rbuf->tail] = 0;
	rbuf->tail = (rbuf->tail + 1) % RBUF_SIZE;
	return (0);
}

int
main(int argc, char **argv)
{
	int i = 0;
	int choice = 0;
	int data = 0;

	for (i = 0; i < RBUF_SIZE; i++) {
		rbuf.buffer[i] = 0;
	}

	while (1) {
		printf("1. Add\n2. Remove\n3. Debug\n4. Exit\nChoice: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1: // insert
				printf("Value: ");
				scanf("%d", &data);
				if (ring_buffer_insert(&rbuf, data) < 0) {
					printf("Ring Buffer Full\n");
				}
				ring_buffer_dump(&rbuf);
				break;
			case 2: // remove
				if (ring_buffer_remove(&rbuf) < 0) {
					printf("Ring Buffer Empty\n");
				}
				ring_buffer_dump(&rbuf);
				break;
			case 3:
				ring_buffer_dump(&rbuf);
				break;
			case 4:
				exit(0);
				break;
			default:
				break;
		}

	}
	return (0);
}
