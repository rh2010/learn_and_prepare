#include "../my_header.h"

/*
 * Implemenet a binary search tree.
 *
 *
 * Add node,
 * Delete node
 *
 * Traversals.
 *  - In-order
 *  - Pre-order
 *  - Post-order
 *  - Euler
 *
 * Is tree a complete binary tree
 * Is tree a full binary tree
 *
 * Find the depth / height of the tree
 * Select a node with rank 'k': Find the k-th node of the tree
 * Rank of an 'element': Given a element, find how many elements are smaller than the 'element'.
 * Size / number of nodes: Find the total number of elements of the tree.
 */
struct bst {
	int data;
	struct bst* left;
	struct bst* right;
};

struct bst *root;

/*
 * Allocate and initialize a new node for the bst
 */
struct bst*
bst_new_node(int data)
{
	struct bst* new;

	new = (struct bst*)malloc(sizeof (struct bst));
	if (new == NULL) {
		printf("No memory\n");
		return NULL;
	}
	new->data = data;
	new->left = NULL;
	new->right = NULL;

	return new;
}

void
bst_insert_node(struct bst* root, struct bst* new)
{
	ASSERT(root);

	if (root->data >= new->data) {
		// add to left
		if (root->left == NULL) {
			// add here
			root->left = new;
		} else {
			// add to the left sub-tree
			bst_insert_node(root->left, new);
		}
	} else { // root->data < new->data
		// add to right
		if (root->right == NULL) {
			// add here.
			root->right = new;
		} else {
			// add to the right sub-tree.
			bst_insert_node(root->right, new);
		}
	}
}

/*
 * Returns the node is 'data' is found else,
 * returns NULL.
 *
 */
struct bst*
bst_find_node(struct bst* root, int data)
{
	if (root == NULL) {
		return NULL;
	}

	if (root->data == data) {
		return root;
	}

	if (data < root->data) {
		// search in left sub-tree
		return bst_find_node(root->left, data);
	} else {
		// search in right sub-tree
		return bst_find_node(root->right, data);
	}
}

struct bst*
bst_find_node_iterative(struct bst* root, int data)
{
	struct bst *res = NULL, *temp = root;

	while (temp !=  NULL) {
		if (temp->data == data) {
			res = temp;
			break;
		}
		if (data < temp->data) {
			// go left
			temp = temp->left;
		} else {
			// go right
			temp = temp->right;
		}
	}

	return res;
}

/*
 * returns the node with minimum value in the tree.
 */
struct bst*
bst_get_min(struct bst* root)
{
	struct bst* node = root;

	while(node->left != NULL) {
		node = node->left;
	}

	return node;
}

/*
 * Delete the node with value data.
 *
 * Return the root of the new tree.
 */
struct bst*
bst_delete_node(struct bst* root, int data)
{
	struct bst* temp;

	if (root == NULL) {
		return NULL;
	}

	// base case.
	if (root->data == data) {
		// zero or one child case.
		if (root->left == NULL || root->right == NULL) {
			temp = (root->left) ? (root->left) : (root->right);

			if (temp == NULL) {
				// zero children case.
				temp = root;
				root = NULL;
			} else {
				// one child case.
				// put value of child in root and delete child.
				root->data = temp->data;
				root->left = temp->left;
				root->right = temp->right;
			}
			free(temp);
		} else {
			// two child case.
			// Get the inorder successor, smallest value in the
			// right sub-tree
			temp = bst_get_min(root->right);
			root->data = temp->data;
			root->right = bst_delete_node(root->right, root->data);
		}
		return root;
	}

	if (data < root->data) {
		root->left = bst_delete_node(root->left, data);
	} else {
		root->right = bst_delete_node(root->right, data);
	}

	return root;
}

void
bst_walk_inorder(struct bst* root)
{
	if (root == NULL) {
		return;
	}

	bst_walk_inorder(root->left);
	printf("%d ", root->data);
	bst_walk_inorder(root->right);
}

void
bst_walk_preorder(struct bst* root)
{
	if (root == NULL) {
		return;
	}

	printf("%d ", root->data);
	bst_walk_preorder(root->left);
	bst_walk_preorder(root->right);
}

void
bst_walk_postorder(struct bst* root)
{
	if (root == NULL) {
		return;
	}
	bst_walk_postorder(root->left);
	bst_walk_postorder(root->right);
	printf("%d ", root->data);
}

void
bst_walk_euler(struct bst* root)
{
	if (root == NULL) {
		return;
	}
	printf("%d ", root->data);
	bst_walk_euler(root->left);
	printf("%d ", root->data);
	bst_walk_euler(root->right);
	printf("%d ", root->data);
}

int
bst_height(struct bst *root)
{
	int lh, rh;

	if (root == NULL) {
		return 0;
	}
	return (MAX(bst_height(root->left), bst_height(root->right)) + 1);
}

int
bst_nodes(struct bst *root)
{
	if (root == NULL) {
		return 0;
	}
	return (bst_nodes(root->left) + 1 + bst_nodes(root->right));
}

int
bst_size(struct bst* root)
{
	return bst_nodes(root);
}

void
bst_print_current_level(struct bst *root, int level)
{
	if (root == NULL) {
		return;
	}
	if (level == 1) {
		printf("%d ", root->data);
	} else if ( level > 1) {
		bst_print_current_level(root->left, level-1);
		bst_print_current_level(root->right, level-1);
	}
}

void
bst_walk_level_order(struct bst* root)
{
	int height, i;
	height = bst_height(root);
	printf("Height of bst: %d\n", height);

	for (i = 1; i <= height; i++) {
		bst_print_current_level(root, i);
	}
}

void
search_data_in_bst(struct bst* root, int data, bool use_iterative)
{
	struct bst* temp;

	if (use_iterative) {
		temp = bst_find_node_iterative(root, data);
	} else {
		temp = bst_find_node(root, data);
	}

	if (temp) {
		printf("%d is present in the tree\n", data);
		if (data != temp->data) {
			printf("Search is wrong\n");
		}
	} else {
		printf("%d not present in the tree\n", data);
	}
}

void
doubleTree(struct bst *root)
{
	struct bst* new, *temp;

	if (root == NULL) {
		return;
	}
	doubleTree(root->left);
	doubleTree(root->right);

	new = bst_new_node(root->data);
	if (new == NULL) {
		printf("No memory for the new node\n");
	}
	temp = root->left;
	root->left = new;
	new->left = temp;
}

void
bstPrintPaths(struct bst *root, int *arr, int idx)
{
	int i;

	if (root == NULL) {
		return;
	}

	arr[idx++] = root->data;
	// if leaf node, then, print the path
	if ((root->left == NULL) &&
		(root->right == NULL)) {
		for (i = 0; i < idx; i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
	}

	bstPrintPaths(root->left, arr, idx);
	bstPrintPaths(root->right, arr, idx);
}

bool
bstHasPathSum(struct bst *root, int sum)
{
	int newSum;
	bool lRes, rRes;

	if (root->left == NULL && root->right == NULL) {
		return ((sum - root->data) == 0);
	}
	lRes = rRes = FALSE;
	newSum = sum - root->data;

	if (root->left) {
		lRes = bstHasPathSum(root->left, newSum);
	}
	if (root->right) {
		rRes = bstHasPathSum(root->right, newSum);
	}

	return (lRes || rRes);
}

bool
bst_is_full(struct bst *root)
{
	if (root == NULL) {
		return TRUE;
	}
	if ((root->left == NULL && root->right != NULL) ||
		(root->right == NULL && root->left != NULL)) {
		// if the tree has a node with just 1 child, then
		// it is not a FULL binary tree.
		return FALSE;
	}
	return (bst_is_full(root->left) && bst_is_full(root->right));
}

bool
bst_check_complete(struct bst *root, int index, int node_count)
{
	if (root == NULL) {
		return TRUE;
	}
	if (index >= node_count) {
		printf("Index: %d, node_count: %d\n", index, node_count);
		return FALSE;
	}
	return (bst_check_complete(root->left, (index * 2 + 1), node_count) &&
		   bst_check_complete(root->right, (index * 2 + 2), node_count));
}

bool
bst_is_complete(struct bst *root)
{
	int num_nodes;
	int index = 0;

	if (root == NULL) {
		return TRUE;
	}

	num_nodes = bst_nodes(root);
	printf("BST has %d nodes\n", num_nodes);
	return bst_check_complete(root, index, num_nodes);
}

/*
 * Select the node with rank 'r'
 */
struct bst*
bst_select(struct bst* root, int r)
{
	int local_rank;

	if (root == NULL) {
		return NULL;
	}
	local_rank = 1 + bst_size(root->left);

	// base case.
	if (r == local_rank) {
		return root;
	}

	if (r < local_rank) {
		// check left
		return bst_select(root->left, r);
	} else {
		// check right
		return bst_select(root->right, r - local_rank);
	}
}

/*
 * Find the rank of the element 'e'
 */
int
bst_rank(struct bst* root, int e)
{
	if (root == NULL) {
		return 0;
	}

	// base case
	if (root->data == e) {
		return (bst_size(root->left) + 1);
	}

	// go left
	if (e < root->data) {
		return bst_rank(root->left, e);
	} else {
		return (bst_size(root->left) + 1 + bst_rank(root->right, e));
	}
}

int
main(int argc, char** argv)
{
	int count = 0;
	int i;
	struct bst* temp;
	int arr[10];
	int choice = 0;

	if (argc <= 3) {
		printf("Too few params\n");
		printf("usage: ./bst <count of elements> <count number of elements>");
		exit(-1);
	}
	count = atoi(argv[1]);

	if (argc != (count+2)) {
		printf("Wrong count of elements, should be: %d, given: %d\n", count,
			   (argc-2));
		exit(-1);
	}

	// Create the root node.
	root = bst_new_node(atoi(argv[2]));
	if (root == NULL) {
		printf("Can't create root node\n");
		exit(-1);
	}

	// populate the rest of the tree.
	for (i=0; i < (count-1); i++) {
		temp = bst_new_node(atoi(argv[i+3]));
		if (temp == NULL) {
			printf("Can't add a new node to the tree\n");
			printf("Only %d nodes were added\n", i+1);
			exit(-1);
		}
		bst_insert_node(root, temp);
	}
	printf("Added %d nodes\n", i+1);

	printf("Checking traversals\n");
	// print the tree in in-order
	//
	printf("Inorder Traversal: \n");
	bst_walk_inorder(root);
	printf("\n");
	// print the tree in pre-order
	//
	printf("Pre-order Traversal: \n");
	bst_walk_preorder(root);
	printf("\n");

	// print the tree in post-order
	//
	printf("Post-order Traversal: \n");
	bst_walk_postorder(root);
	printf("\n");

	// print the tree in Euler 
	//
	printf("Euler Traversal: \n");
	bst_walk_euler(root);
	printf("\n");

	// print the tree in Level Order 
	//
	printf("Level-Order Traversal: \n");
	bst_walk_level_order(root);
	printf("\n");

	printf("Checking seaching in the tree\n");
	// Check if 70 is present in the tree
	//
	search_data_in_bst(root, 70, TRUE);
	// Check if 32 is present in the tree
	//
	search_data_in_bst(root, 32, FALSE);
	// Check if 20 is present in the tree
	//
	search_data_in_bst(root, 20, FALSE);
	// Check if 60 is present in the tree
	//
	search_data_in_bst(root, 60, TRUE);
	printf("\n");

	printf("hasPathSum: 18 ? %s\n", (bstHasPathSum(root, 18)) ? "YES":"NO");
	printf("hasPathSum: 22 ? %s\n", (bstHasPathSum(root, 22)) ? "YES":"NO");
	printf("hasPathSum: 30 ? %s\n", (bstHasPathSum(root, 30)) ? "YES":"NO");
	printf("hasPathSum: 45 ? %s\n", (bstHasPathSum(root, 45)) ? "YES":"NO");

	// doubleTree()
	/*
	printf("doubling the tree\n");
	doubleTree(root);
	bst_walk_inorder(root);
	printf("\n");
	bst_walk_preorder(root);
	printf("\n");
	bst_walk_postorder(root);
	printf("\n");
	*/

	// print path from the root node to each leaf node.
	//bstPrintPaths(root, arr, 0);

	// check if the tree is a complete binary tree
	//
	printf("This is%sa complete bst\n", bst_is_complete(root)? " " : " not ");
	// check if the tree is a full binary tree
	//
	printf("This is%sa full bst\n", bst_is_full(root)? " " : " not ");
	//
	//
	while(TRUE) {
		printf("\n1) Select\n2) Rank\n3) Delete\n4) Exit\nChoice: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				printf("Rank: ");
				scanf("%d", &i);
				// select the node with rank 'i'
				temp = bst_select(root, i);
				if (temp == NULL) {
					printf("No element with rank '%d'\n", i);
				} else {
					printf("Element with rank '%d' is '%d'\n", i, temp->data);
				}
				break;
			case 2:
				printf("Element: ");
				scanf("%d", &i);
				// find the rank of the element 'i'
				printf("Rank of element '%d' is '%d'\n", i, bst_rank(root, i));
				break;
			case 3:
				// exit
				printf("Value: ");
				scanf("%d", &i);
				root = bst_delete_node(root, i);

				printf("Inorder Traversal: \n");
				bst_walk_inorder(root);
				printf("\n");
				break;
			case 4:
				// exit
				printf("Done\n");
				exit(0);
			default:
				printf("Wrong choice\n");
				break;
		}
	}
	return 0;
}