#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedListNode {
   int val;
   struct LinkedListNode *next;
} LinkedListNode;

typedef struct linked_list_head {
	LinkedListNode *list;

	//For debug
	int count;
	//lock;
} linked_list_head;

void
reverseList(linked_list_head *head)
{
	LinkedListNode *temp, *prev, *next;

	prev = NULL;
	temp = head->list;

	while(temp!= NULL) {
		next = temp->next;
		temp->next = prev;

		if (next == NULL) {
			// last node, re-adjust the head.
			head->list = temp;	
		}
		prev = temp;
		temp = next;
	}
}

void
displayList(linked_list_head *head)
{
	LinkedListNode *first, *temp;

	if (head == NULL) {
		printf("NULL\n");
		return;
	}
	printf("List has %d elements\n", head->count);

	first = temp = head->list;

	while(temp != NULL) {
		// the actual value
		printf("%d ", temp->val);

		if (temp->next == NULL) {
			printf("\n");
		} else {
			printf("-> ");
		}
		temp = temp->next;
	}
}

LinkedListNode*
getNode(int val)
{
	LinkedListNode *new = NULL;

	new = (LinkedListNode *)malloc(sizeof (LinkedListNode));
	if (new == NULL) {
		printf("No memory for a new node\n");
		return (NULL);
	}

	// Initialize the values.
	new->val = val;
	new->next = NULL;

	return new;
}

void removeAll(linked_list_head *head, int val)
{
	LinkedListNode *first;
	LinkedListNode *temp;
	LinkedListNode *prev;

	first = temp = head->list;
	prev = NULL;

	while (temp != NULL) {
		if (temp->val == val) {

			if (prev == NULL) {

				head->list = temp->next;
				free(temp);
				temp = head->list;
			} else {
				prev->next = temp->next;
				free(temp);
				temp = prev->next;
			}
			//
			head->count--;
		} else {
			prev = temp;
			temp = temp->next;
		}
	}
}

/*
 * return 0 for success
 * 	-1 for failure
 */
int
addNode(linked_list_head *head, int val)
{
	LinkedListNode *temp, *new;

	temp = new = NULL;

	printf("Node count: %d\n", head->count);
	temp = head->list;

	new = getNode(val);
	if (new == NULL) {
		return -1;
	}

	/*
	 * special case for the first node of the list.
	 */
	if (temp == NULL) {
		head->list = new;
		head->count = 1;
		return (0);
	}

	// goto the end of the list.
	while(temp->next != NULL) {
		temp = temp->next;
	}

	// attach the new node.
	temp->next = new;

	// adjust the count.
	head->count++;

	return(0);
}

int
main(int argc, char **argv)
{
	int count = 0;
	int val;
	linked_list_head sll;
	int choice = 0;
	int i;

	if (argc < 2) {
		printf("usage: ./a.out <count> <count number of integers> ..\n");
		exit(-1);
	}
	count = atoi(argv[1]);

	if (argc - 2 != count) {
		printf("%d integers, should be: %d\n", (argc - 2), count);
		printf("usage: ./a.out <count> <count number of integers> ..\n");
		exit(-1);
	}

	sll.count = 0;
	sll.list = NULL;

	for (i = 0; i < count; i++) {
		val = atoi(argv[i+2]);

		printf("Adding node: %d\n", val);
		if (addNode(&sll, val) != 0) {
			printf("Failed to add new Node\n");
			displayList(&sll);
			exit(-1);
		}
	}
	printf("The List:\n");
	displayList(&sll);

	while(1) {
		printf("1) Add\n2) Remove\n3) Display\n4) Reverse\n5) Exit\nChoice: ");
		scanf("%d", &choice);

		switch(choice) {
			case 1: // add node
				printf("Value: ");
				scanf("%d", &val);
				addNode(&sll, val);
				break;
			case 2: // remove node
				printf("Value: ");
				scanf("%d", &val);
				removeAll(&sll, val);
				break;
			case 3: // display list
				displayList(&sll);
				break;
			case 4: // reverse list
				reverseList(&sll);
				break;
			case 5: // exit
				// leaking memory, yes!
				exit(0);
				break;
			default:
				break;
		}
	}
	return 0;
}
