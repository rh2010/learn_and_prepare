#include "../util.h"
#include "queue.h"

/*
 * Implement intersection of binary search trees.
 * Given 2 BST(s) print out the common nodes from the two trees
 */

struct bst {
	int data;
	struct bst* left;
	struct bst* right;
    bool visited;
};

struct bst *root;
struct bst *root2;

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
    new->visited = FALSE;

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

	/*
	 * Left sub tree contains data which is less
	 * than or equal to the data at the root of
	 * the tree.
	 */
	if (data <= root->data) {
		// search in left sub-tree
		return bst_find_node(root->left, data);
	} else {
		// search in right sub-tree
		return bst_find_node(root->right, data);
	}
}

bool
visit_node(struct bst* node)
{
    assert(node);
    node->visited = TRUE;
}

bool
node_visited(struct bst* node)
{
    assert(node);
    return node->visited;
}

void
bst_walk_inorder_iter(struct bst* root, struct bst* root2)
{
    struct bst* temp = NULL;
    struct bst* temp2 = NULL;
    if (root == NULL) {
        return;
    }

    if (root2 == NULL) {
        return;
    }

    // Init the stack
    stack_head_t s;
    stack_init(&s);

    stack_head_t s2;
    stack_init(&s2);

    // Push the root to the stack
    temp = root;
    push(&s, root);

    temp2 = root2;
    push(&s2, root2);

    // iter
    while (!stack_is_empty(&s) && !stack_is_empty(&s2)) {
        // pop the top
        temp = (struct bst*)pop(&s);

        if (node_visited(temp)) {
            printf("%d ", temp->data);
            continue;
        }

        // if no children, then print and continue
        if ((!temp->left) && (!temp->right)) {
            printf("%d ", temp->data);
            continue;
        }

        // right
        if (temp->right) {
            push(&s, temp->right);
        }

        // visit and push the root again.
        visit_node(temp);
        push(&s, temp);

        // left
        if (temp->left) {
            push(&s, temp->left);
        }
    }

    stack_uninit(&s);
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

int
main(int argc, char** argv)
{
	int total = 0;
	int num_nodes_1 = 0;
	int num_nodes_2 = 0;

	int i;
	struct bst* temp;
	struct bst* temp2;
	int arr[10];
	int choice = 0;

	if (argc <= 3) {
		printf("Too few params\n");
		printf("usage: ./bst <count of total elements> <# nodes in 1st tree>"
				" <elements of 1st tree> <# nodes in 2nd tree> <elements of "
				"2nd tree>\n");
		exit(-1);
	}

	total = atoi(argv[1]);

	if (argc != (total+4)) {
		printf("Wrong count of elements, should be: %d, given: %d\n", total,
			   (argc-2));
		exit(-1);
	}

	num_nodes_1 = atoi(argv[2]);

	// Create the root node.
	root = bst_new_node(atoi(argv[3]));
	if (root == NULL) {
		printf("Can't create root node\n");
		exit(-1);
	}

	// populate the rest of the tree.
	for (i=0; i < (num_nodes_1-1); i++) {
		temp = bst_new_node(atoi(argv[i+4]));
		if (temp == NULL) {
			printf("Can't add a new node to the tree\n");
			printf("Only %d nodes were added\n", i+1);
			exit(-1);
		}
		bst_insert_node(root, temp);
	}
	printf("Tree1: Added %d nodes\n", i+1);

	assert(num_nodes_1 == i+1);

	int pos = num_nodes_1 + 3;
	// Build the seconds tree.
	num_nodes_2 = atoi(argv[pos++]);

	printf("total: %d, 1: %d, 2: %d\n", total, num_nodes_1, num_nodes_2);

	root2 = bst_new_node(atoi(argv[pos++]));
	if (root2 == NULL) {
		printf("Can't create root node\n");
		exit(-1);
	}

	// populate the rest of the tree.
	for (i=0; i < (num_nodes_2-1); i++) {
		temp2 = bst_new_node(atoi(argv[i+pos]));
		if (temp2 == NULL) {
			printf("Can't add a new node to the tree\n");
			printf("Only %d nodes were added\n", i+1);
			exit(-1);
		}
		bst_insert_node(root2, temp2);
	}
	printf("Tree2: Added %d nodes\n", i+1);
	// print the tree in in-order
	//

	printf("Inorder Traversal: 1\n");
	bst_walk_inorder(root);
	printf("\n");

	printf("Inorder Traversal: 2\n");
	bst_walk_inorder(root2);
	printf("\n");
	// print the common nodes in the two trees.
	//
	printf("Intresection: \n");
	//bst_walk_inorder_iter(root, root2);
	printf("\n");

	return 0;
}
