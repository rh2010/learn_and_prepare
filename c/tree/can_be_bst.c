#include "../util.h"

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
/*	printf("root: %d\nsub-array\n", root);
	
	for(i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
*/

	lSize = rSize = 0;

	// left sub-tree starts right after the root
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
	int *arr;
	int op; // 0 => postorder, 1 => inorder, 2 => preorder 

	if (argc <= 4) {
		printf("Too few params\n");
		printf("usage: ./a.out <op  0 => postorder, 1 => inorder, 2 => preorder>"
			   " <count of elements> <count number of elements>\n");
		exit(-1);
	}
	op = atoi(argv[1]);
	count = atoi(argv[2]);

	if (argc != (count+3)) {
		printf("Wrong count of elements, should be: %d, given: %d\n", count,
			   (argc-2));
		exit(-1);
	}

	printf("Size: %d, Op: %d - ", count, op);
	// allocate space for the array.
	//
	arr = (int *)malloc((sizeof (int) * count));
	if (arr == NULL) {
		printf("No memory for the array\n");
		exit(-1);
	}

	// populate the array
	//
	for (i = 0; i < count; i++) {
		arr[i] = atoi(argv[i+3]);
	}

	switch (op) {
		case 0:
			// postorder
			printf("postorder\n");
			printf("The array %s be BST\n", (canBstFromPostorder(arr, count)) ? "can" : "cannot");
			break;
		case 1:
			// inorder
			printf("inorder\n");
			printf("The array %s be BST\n", (canBstFromInorder(arr, count)) ? "can" : "cannot");
			break;
		case 2:
			// preorder
			printf("preorder\n");
			printf("The array %s be BST\n", (canBstFromPreorder(arr, count)) ? "can" : "cannot");
			break;
		default:
			printf("Wrong op\n");
			free(arr);
			exit(-1);
			break;
	}
	free(arr);
	return 0;
}
