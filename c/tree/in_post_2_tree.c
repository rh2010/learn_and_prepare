#include "../util.h"

/*
 * Implement a function to check if from the given traversal
 * in-order / post-order / pre-order 
 * can it represent a binary search tree.
 *
 * TODO:
 *  - Post-Order
 *  - In-Order are pending
 */

struct node {
	int data;
	struct node* left;
	struct node* right;
};

struct node *root;

struct node*
bst_new_node(int data)
{
	struct node* new;

	new = (struct node*)malloc(sizeof (struct node));
	if (new == NULL) {
		printf("No memory\n");
		return NULL;
	}
	new->data = data;
	new->left = NULL;
	new->right = NULL;

	return new;
}

bool
canBstFromPreorder(int *arr, int size)
{
	int root;
	int lIdx, rIdx;
	int lSize, rSize;
	int i;
	
//	printf("size: %d\n", size);

	if (size == 0) 
		return TRUE;
	
	// the first element in the root of the BST
	root = arr[0];
//	printf("root: %d\nsub-array\n", root);
	
	for(i = 0; i < size; i++) {
//		printf("%d ", arr[i]);
	}
//	printf("\n");


	lSize = rSize = 0;

	// left sub-tree starts right after the roo
	lIdx = 1;
	for (i=1; arr[i] < root && i < size; i++);

	// right sub-tree
	rIdx = i;
//	printf("lIdx: %d, rIdx: %d\n", lIdx, rIdx);

	// size of the left sub-tree
	lSize = rIdx - lIdx;

	// size of the right sub-array
	rSize = size - rIdx;
//	printf("lSize: %d, rSize: %d\n", lSize, rSize);

	// validate if all the elements in the right subarray are greater than
	// 'root'
	for(i = rIdx; i < size && arr[i] > root; i++);
//	printf("i: %d, rIdx: %d, rSize: %d\n", i, rIdx, rSize);

	if (i != (size)) {
//		printf("returning false\n");
		return FALSE;
	}

//	printf("\n\n");
	// check in the left sub-array and the right-sub-array
	return (canBstFromPreorder((int *)(arr+lIdx), lSize) &&
			canBstFromPreorder((int *)(arr+rIdx), rSize));
}

bool
canBstFromPostorder(int *arr, int size)
{
	return FALSE;
}

bool
canBstFromInorder(int *arr, int size)
{
	return FALSE;
}

int
main(int argc, char** argv)
{
	int count = 0;
	int i;
	int *in, *post;

	if (argc <= 4) {
		printf("Too few params\n");
		printf("usage: ./a.out usage: <count of elements> <inorder: count number of elements>  <postorder: count number of elements>\n");
		exit(-1);
	}
	count = atoi(argv[1]);

	if (argc != (2 * count + 2)) {
		printf("Wrong count of elements, should be: %d, given: %d\n", count,
			   (argc-2));
		exit(-1);
	}

	printf("Size: %d, Op: %d - ", count, op);
	// allocate space for the array.
	//
	in = (int *)malloc((sizeof (int) * count));
	if (in == NULL) {
		printf("No memory for the array\n");
		exit(-1);
	}

	post = (int *)malloc((sizeof (int) * count));
	if (post == NULL) {
		printf("No memory for the array\n");
		exit(-1);
	}

	// populate the array
	//
	for (i = 0; i < count; i++) {
		in[i] = atoi(argv[i+2]);
	}
	for (i = 0; i < count; i++) {
		post[i] = atoi(argv[i+2+count]);
	}

	free(in);
	free(post);
	return 0;
}
