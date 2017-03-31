#include "../my_header.h"

#define LCHILD(x)	((x)->left)
#define RCHILD(x)	((x)->right)
#define HEIGHT(x)	((x) ? (x)->height : 0)

/*
 * http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 */
struct avl_node {
	int data;
	int height;
	struct avl_node *left;
	struct avl_node *right;
};

// root of the avl tree
struct avl_node* avl_root;

struct avl_node*
avl_new_node(int data)
{
	struct avl_node *new = NULL;

	new = (struct avl_node*)malloc(sizeof (struct avl_node));
	if (new == NULL) {
		printf("No Memory\n");
		goto out;
	}

	new->left = new->right = NULL;
	new->data = data;
	new->height = 1;
//	printf("New node: [%p] : [%d]\n", new, new->data);
out:
	return new;
}

struct avl_node*
avl_right_rotate(struct avl_node *root)
{
	struct avl_node* lc;

	printf("Right Rotate: %d\n", root->data);
	lc = LCHILD(root);

	LCHILD(root) = RCHILD(LCHILD(root));
	RCHILD(lc) = root;

	// adjust the height
	root->height = MAX(HEIGHT(LCHILD(root)), HEIGHT(RCHILD(root))) + 1;;
	lc->height = MAX(HEIGHT(LCHILD(lc)), HEIGHT(RCHILD(lc))) + 1;;

	return lc;
}

struct avl_node*
avl_left_rotate(struct avl_node *root)
{
	struct avl_node* rc;

	printf("Left Rotate: %d\n", root->data);
	rc = RCHILD(root);

	RCHILD(root) = LCHILD(RCHILD(root));
	LCHILD(rc) = root;

	// adjust the height
	//
	root->height = MAX(HEIGHT(LCHILD(root)), HEIGHT(RCHILD(root))) + 1;;
	rc->height = MAX(HEIGHT(LCHILD(rc)), HEIGHT(RCHILD(rc))) + 1;;

	return rc;
}

int
avl_get_balance(struct avl_node* root)
{
	return (HEIGHT(LCHILD(root)) - HEIGHT(RCHILD(root)));
}

/*
 * Return: The tree with the newly added node.
 */
struct avl_node*
avl_insert_node(struct avl_node* tree, int data)
{
	int diff;
	struct avl_node* new;

	if (tree == NULL) {
		// add the node here.
		new = avl_new_node(data);
		if (new == NULL) {
			printf("Can't create a new node\n");
			return NULL;
		}
		return new;
	}

	if (data <= tree->data) {
		// goto left
		tree->left = avl_insert_node(LCHILD(tree), data);
		if (tree->left == NULL) {
			printf("Can't add a new node - left\n");
			return NULL;
		}
	} else {
		// goto right
		tree->right = avl_insert_node(RCHILD(tree), data);
		if (tree->right == NULL) {
			printf("Can't add a new node - right\n");
			return NULL;
		}
	}

	// update height
	tree->height = 1 + MAX(HEIGHT(RCHILD(tree)), HEIGHT(LCHILD(tree)));

	// check if there is an imbalalce
	diff = avl_get_balance(tree);

	/*
	 * http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
	 */
	if (abs(diff) > 1) {
		printf("Performing rotations diff [%d]\n", diff);

		// Left Left Case
		//  : 1 right rotation
		if (diff > 1 && data < tree->left->data) {
			printf("Left Left Case\n");
			return avl_right_rotate(tree);
		}

		// Left Right Case
		//  : 2 rotations
		//   First left rotate (becomes a Left Left Case)
		//   Second, right rotate
		//
		if (diff > 1 && data > tree->left->data) {
			printf("Left Right Case\n");
			tree->left = avl_left_rotate(tree->left);
			return avl_right_rotate(tree);
		}

		// Right Right Case
		//   : 1 Left rotation 
		//
		if (diff < -1 && data > tree->right->data) {
			printf("Right Right Case\n");
			return avl_left_rotate(tree);
		}

		// Right Left Case
		//   : 2 rotations
		//     First, right rotation
		//     Second, left rotation
		//
		if (diff < -1 && data < tree->right->data) {
			printf("Right Left Case\n");
			tree->right = avl_right_rotate(tree->right);
			return avl_left_rotate(tree);
		}
	}
	return tree;
}

void
avl_visit_inorder(struct avl_node* tree)
{
	if (tree == NULL) {
		return;
	}
	avl_visit_inorder(tree->left);
	printf("[%d: h-%d] ", tree->data, tree->height);
	avl_visit_inorder(tree->right);
}

void
avl_visit_preorder(struct avl_node* tree)
{
	if (tree == NULL) {
		return;
	}
	printf("[%d: h-%d] ", tree->data, tree->height);
	avl_visit_preorder(tree->left);
	avl_visit_preorder(tree->right);
}

struct avl_node*
avl_tree_delete_node(struct avl_node* tree, int data)
{
	return NULL;
}

int
main(int argc, char **argv)
{
	int count = 0;
	int i;
	struct avl_node* temp;
	//int arr[10];
	int choice = 0;

	if (argc <= 3) {
		printf("Too few params\n");
		printf("usage: ./avl <count of elements> <count number of elements>");
		exit(-1);
	}
	count = atoi(argv[1]);

	if (argc != (count+2)) {
		printf("Wrong count of elements, should be: %d, given: %d\n", count,
			   (argc-2));
		exit(-1);
	}

	// Create the root node.
	avl_root = avl_insert_node(avl_root, atoi((argv[2])));
	if (avl_root == NULL) {
		printf("Can't create root node\n");
		exit(-1);
	}

	// populate the rest of the tree.
	for (i=0; i < (count-1); i++) {
		printf("[%d] Adding node %d\n", i, atoi(argv[i+3]));
		temp = avl_insert_node(avl_root, atoi(argv[i+3]));
		if (temp == NULL) {
			printf("Can't add a new node to the tree\n");
			printf("Only %d nodes were added\n", i+1);
			exit(-1);
		}
	}
	printf("Added %d nodes\n", i+1);

	// print the tree in in-order
	//
	printf("Inorder Traversal: \n");
	avl_visit_inorder(avl_root);
	printf("\n");
	// print the tree in pre-order
	//
	printf("Preorder Traversal: \n");
	avl_visit_preorder(avl_root);
	printf("\n");

	while(1) {
		printf("1) Insert, 2) Inorder, 3) Pre-order, 4)Exit, Choice: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1: // insert
				printf("Value: \n");
				scanf("%d", &i);
				temp = avl_insert_node(avl_root, i);
				if (temp == NULL) {
					printf("Can't add a new node to the tree\n");
					printf("Only %d nodes were added\n", i+1);
					exit(-1);
				}
				break;
			case 2:
				avl_visit_inorder(avl_root);
				printf("\n");
				break;
			case 3:
				avl_visit_preorder(avl_root);
				printf("\n");
				break;
			case 4:
				exit(0);
				break;
			default:
				printf("\n");
				break;
		}
	}

	return 0;
}
