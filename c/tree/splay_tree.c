#include "../util.h"

/*
 * Implement a splay tree (following operations):
 *
 * 	Insert
 * 		- Usual operation
 * 	Delete
 * 		- Usual operation
 * 	Find
 * 		- Find a node and splay to the top
 * 		- this will need us to implement splay() operation.
 * 		- rotations
 *
 * 	Merge
 * 		- Splay trees provide a nice way to implement merging of two trees.
 *
 * 	Split
 * 		- Splay trees provide a nice way to implement splitting of a
 * 		  single tree into two separate trees.
 */

struct bst_node {
	int data;
	struct bst_node *parent;
	struct bst_node *left;
	struct bst_node *right;
};

struct bst_node *splay_tree;

struct bst_node* splay_tree_find(struct bst_node *root, int key);
void splay(struct bst_node **root, struct bst_node *node);
void dump_tree();

/*
 * Returns the node is 'data' is found else,
 * returns where the node with key 'data' can
 * be added. 
 *
 * If the node to be found is the max node in the tree
 * then, it returns NULL
 *
 */
struct bst_node*
bst_find_node(struct bst_node* root, int data)
{
	struct bst_node *res = NULL, *temp = root;

	while (temp != NULL) {
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
 * This splays the node with key 'key' 
 * and returns the new root of the tree.
 */
struct bst_node*
splay_tree_find(struct bst_node *root, int key)
{
	struct bst_node *temp;

	temp = bst_find_node(root, key);

	if (temp != NULL) {
		splay(&splay_tree, temp);
	}
	return temp;
}

void
update(struct bst_node *node)
{
	assert(node != NULL);

	// update left's parent
	if (node->left != NULL) {
		node->left->parent = node;
	}

	// update right's parent
	if (node->right != NULL) {
		node->right->parent = node;
	}

}

void
single_rotation(struct bst_node *node)
{
	struct bst_node *parent;
	parent = node->parent;

	assert(node != NULL);
	if (parent == NULL) {
		return;
	}
	printf("\tSingle Rotation [%d] : ", node->data);

	struct bst_node *grand_parent = parent->parent;

	if (parent->left == node) {
		struct bst_node *q = node->right;
		// right rotate
		//
		printf("RR\n");
		node->right = parent;
		parent->left = q;
	} else {
		// left rotate
		printf("LR\n");
		struct bst_node *q = node->left;

		node->left = parent;
		parent->right = q;
	}
	update(parent);
	update(node);

	node->parent = grand_parent;

	// update grand_parent;
	if (grand_parent != NULL) {
		if (grand_parent->left == parent) {
			grand_parent->left = node;
		} else {
			grand_parent->right = node;
		}
	}
}

void
double_rotation(struct bst_node *node)
{
	struct bst_node *parent;

	assert(node != NULL);

	parent = node->parent;
	assert(parent != NULL);
	assert(parent->parent != NULL);

	// find out if it is zig-zig case or zig-zag case
	//
	// difference between zig-zig case and zig-zag case
	//
	// Given the following tree:
	//
	//	 	   10
	//	 	  /   \
	//	 	 /     \
	//      8      20
	//	   / \    /  \
	//	  5   9  15  30
	//
	// Zig-Zig:
	// 	If we have to splay 30
	// 	code becomes:
	// 		single_rotation(20)
	// 		single_rotation(30)
	//
	// Zig-Zag:
	//  If we have to splay 15 / 9
	//  For 15:
	//  	single_rotation(15)
	//  	single_rotation(15)
	//
	//  For 9:
	//  	single_rotation(9)
	//  	single_rotation(9)
	//
	//  So for Zig-Zig case:
	//  	single_rotation(parent)
	//  	single_rotation(self)
	//
	//  and for Zig-Zag case:
	//  	single_rotation(self)
	//  	single_rotation(self)
	if (parent->left == node && parent->parent->left == parent) {
		// zig-zig case
		printf("\tZig-Zig : RR\n");
		single_rotation(parent);
		single_rotation(node);
	} else if (parent->right == node && parent->parent->right == parent) {
		// zig-zig case
		printf("\tZig-Zig : LR\n");
		single_rotation(parent);
		single_rotation(node);
	} else {
		printf("\tZig-Zag \n");
		// zig-zag case
		single_rotation(node);
		single_rotation(node);
	}
}

/*
 * Splay the tree starting at 'node'
 */
void
splay(struct bst_node **root, struct bst_node *node)
{
	assert(*root != NULL);

	if (node == NULL) {
		return;
	}
	printf("Splay:\n");
	while (node->parent != NULL) {
		if (node->parent->parent == NULL) {
			// on single rotation
			printf("\n\tSingle Rotation\n");
			single_rotation(node);
			break;
		}
		printf("\n\tDouble Rotation\n");
		// else, do zig-zig or zig-zag
		double_rotation(node);
	}
	*root = node;
}

int
bst_nodes(struct bst_node *root)
{
	if (root == NULL) {
		return 0;
	}
	return (bst_nodes(root->left) + 1 + bst_nodes(root->right));
}

bool
bst_check_complete(struct bst_node *root, int index, int node_count)
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
bst_is_complete(struct bst_node *root)
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
 * Allocate and initialize a new node for the bst
 */
struct bst_node*
bst_new_node(int data)
{
	struct bst_node* new;

	new = (struct bst_node*)malloc(sizeof (struct bst_node));
	if (new == NULL) {
		printf("No memory\n");
		return NULL;
	}
	new->data = data;
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;

	return new;
}

void
bst_insert_node(struct bst_node* root, struct bst_node* new)
{
	ASSERT(root);

	if (root->data >= new->data) {
		// add to left
		if (root->left == NULL) {
			// add here
			root->left = new;
			new->parent = root;
		} else {
			// add to the left sub-tree
			bst_insert_node(root->left, new);
		}
	} else { // root->data < new->data
		// add to right
		if (root->right == NULL) {
			// add here.
			root->right = new;
			new->parent = root;
		} else {
			// add to the right sub-tree.
			bst_insert_node(root->right, new);
		}
	}
}

/*
 * returns the node with minimum value in the tree.
 *
 * This is the left-most node in the tree.
 */
struct bst_node*
bst_get_min(struct bst_node* root)
{
	struct bst_node* node = root;

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
struct bst_node*
bst_delete_node(struct bst_node* root, int data)
{
	struct bst_node* temp;

	// base case.
	if (root == NULL) {
		return NULL;
	}

	// Handle the current case.
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

				// Adjust the parent pointers of temp's children
				if (root->left != NULL) {
					root->left->parent = root;
				}
				if (root->right != NULL) {
					root->right->parent = root;
				}
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

	// recurse down the tree.
	if (data < root->data) {
		root->left = bst_delete_node(root->left, data);
	} else {
		root->right = bst_delete_node(root->right, data);
	}

	return root;
}
void
bst_verify_parent(struct bst_node *root)
{
	assert(root != NULL);

	// check left child
	if (root->left != NULL) {
		assert(root->left->parent == root);
	}

	// check right child
	if (root->right != NULL) {
		assert(root->right->parent == root);
	}
}

void
bst_walk_inorder(struct bst_node* root)
{
	if (root == NULL) {
		return;
	}

	// verify that the parent pointers are intact
	bst_verify_parent(root);

	bst_walk_inorder(root->left);
	printf("%d ", root->data);
	bst_walk_inorder(root->right);
}

void
bst_walk_preorder(struct bst_node* root)
{
	if (root == NULL) {
		return;
	}

	printf("%d ", root->data);
	bst_walk_preorder(root->left);
	bst_walk_preorder(root->right);
}

void
bst_walk_postorder(struct bst_node* root)
{
	if (root == NULL) {
		return;
	}
	bst_walk_postorder(root->left);
	bst_walk_postorder(root->right);
	printf("%d ", root->data);
}

void
bst_print_current_level(struct bst_node *root, int level)
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

int
bst_height(struct bst_node *root)
{
	int lh, rh;

	if (root == NULL) {
		return 0;
	}
	return (MAX(bst_height(root->left), bst_height(root->right)) + 1);
}

void
bst_walk_level_order(struct bst_node* root)
{
	int height, i;
	int j; // for tab spaces
	height = bst_height(root);
	printf("Height of bst: %d\n", height);

	for (i = 1; i <= height; i++) {
		bst_print_current_level(root, i);
		printf("\n");
	}
}

void
dump_tree()
{
	printf("Inorder: \n\t");
	bst_walk_inorder(splay_tree);
	printf("\nLevel order: \n\t");
	bst_walk_level_order(splay_tree);

}

int
main(int argc, char** argv)
{
	int count = 0;
	int i;
	struct bst_node* temp;
	int arr[10];
	int choice = 0;

	if (argc <= 3) {
		printf("Too few params\n");
		printf("usage: ./bst <count of elements> <count number of elements>\n");
		exit(-1);
	}
	count = atoi(argv[1]);

	if (argc != (count+2)) {
		printf("Wrong count of elements, should be: %d, given: %d\n", count,
			   (argc-2));
		exit(-1);
	}

	// Create the root node.
	splay_tree = bst_new_node(atoi(argv[2]));
	if (splay_tree == NULL) {
		printf("Can't create splay_tree \n");
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
		bst_insert_node(splay_tree, temp);
	}
	printf("Added %d nodes\n", i+1);

	printf("Checking traversals\n");
	// print the tree in in-order
	//
	printf("Inorder Traversal: \n");
	bst_walk_inorder(splay_tree);
	printf("\n");
	// print the tree in pre-order
	//
	printf("Pre-order Traversal: \n");
	bst_walk_preorder(splay_tree);
	printf("\n");

	// print the tree in post-order
	//
	printf("Post-order Traversal: \n");
	bst_walk_postorder(splay_tree);
	printf("\n");

	// print the tree in Level Order 
	//
	printf("Level-Order Traversal: \n");
	bst_walk_level_order(splay_tree);
	printf("\n");

	printf("Checking seaching in the tree\n");
	// Check if 70 is present in the tree
	//
	splay_tree_find(splay_tree, 70);
	// Check if 32 is present in the tree
	//
	splay_tree_find(splay_tree, 32);
	// Check if 20 is present in the tree
	//
	splay_tree_find(splay_tree, 20 );
	// Check if 60 is present in the tree
	//
	splay_tree_find(splay_tree, 60 );
	printf("\n");

	// check if the tree is a complete binary tree
	//
	printf("This is%sa complete bst\n", bst_is_complete(splay_tree)? " " : " not ");
	while(TRUE) {
		printf("\n1) Find\n2) Delete\n3) Print BST (inorder)\n4) Merge\n5) Split\n6)Exit\nChoice: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1: // find
				printf("Key to find: ");
				scanf("%d", &i);
				// select the node with rank 'i'
				temp = splay_tree_find(splay_tree, i);
				if (temp == NULL) {
					printf("No element with key '%d'\n", i);
				} else {
					printf("Element with key '%d' is '%d'\n", i, temp->data);
				}
				printf("printing tree:\n");
                printf("Inorder: \n\t");
                bst_walk_inorder(splay_tree);
				printf("\nLevel order: \n\t");
				bst_walk_level_order(splay_tree);
				break;
			case 2: // Delete
				printf("Value: ");
				scanf("%d", &i);
				splay_tree = bst_delete_node(splay_tree, i);

				printf("Inorder Traversal: \n");
				bst_walk_inorder(splay_tree);
				printf("\n");
				break;
			case 3: // inorder traversal
                printf("BST\n");
                bst_walk_inorder(splay_tree);
                break;
			case 4: // Merge
				printf("Not Implemented\n");
				break;
			case 5: // Split
				printf("Not Implemented\n");
				break;
			case 6:
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
