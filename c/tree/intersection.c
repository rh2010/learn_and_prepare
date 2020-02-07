#include "../util.h"
#include "queue.h"

/*
 * Implement intersection of binary search trees.
 * Given 2 BST(s) print out the common nodes from the two trees
 *
 * bst_intersection2() = The correct solution
 */

struct bst {
	int data;
	struct bst* left;
	struct bst* right;
    bool visited;
};

/*
 * We need 2 trees.
 */
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

// This solution is too complicated / un-necessarily complex.
void
bst_intersection(struct bst* root, struct bst* root2)
{
    struct bst* temp = NULL;
    struct bst* temp2 = NULL;

    bool node1_done = FALSE;
    bool node2_done = FALSE;

    if (root == NULL || root2 == NULL) {
        return;
    }

    // Init the stack for traversal
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
		// start with nodes are not done.
		node1_done = FALSE;
		node2_done = FALSE;

        // pop the top
        temp = (struct bst*)pop(&s);
        temp2 = (struct bst*)pop(&s2);


		// If the node is marked visited or it does not have any children
		// then, this node is considered done and is a candidate to be
		// printed (for traversal)!
        if (node_visited(temp) ||
            ((!temp->left) && (!temp->right))) {
            node1_done = TRUE;
        }

        if (node_visited(temp2) ||
            ((!temp2->left) && (!temp2->right))) {
            node2_done = TRUE;
        }

		// If nodes for both the tree are done, then,
		// 1. If they are equal - Print - Found Intersection!
		// 2. Else, The node for which ever tree is smaller, pop that
		//    and push back the node on the stack for the other tree.
		//
		//    And
		//      continue.
        if (node1_done && node2_done) {
            if (temp->data == temp2->data) {
                printf("%d ", temp->data);
            } else if (temp->data < temp2->data) {
                // If the node in tree1 is smaller then put the node in tree2
                // back on the stack.
                push(&s2, temp2);
            } else {
                // and vice-versa
                push(&s, temp);
            }
            continue;
        }

		// Either node for neither of the tree(s) is done or one of the tree
		// is not done.
		//
		// Continue traversal for the tree for whichever the node is not done.
		//

        // Tree 1
        if (!node1_done) {
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
        } else {
            // put back on stack
            push(&s, temp);
        }

        // Tree 2
        if (!node2_done) {
            // right
            if (temp2->right) {
                push(&s2, temp2->right);
            }

            // visit and push the root again.
            visit_node(temp2);
            push(&s2, temp2);

            // left
            if (temp2->left) {
                push(&s2, temp2->left);
            }
        } else {
            // put back on stack
            push(&s2, temp2);
        }
    }

	// Empty the stack if something is pending.
    while (!stack_is_empty(&s)) {
		pop(&s);
	}

    while (!stack_is_empty(&s2)) {
		pop(&s2);
	}

    stack_uninit(&s);
    stack_uninit(&s2);
}

void
bst_intersection2(struct bst* root, struct bst* root2)
{
    struct bst* temp = root;
    struct bst* temp2 = root2;

    bool node1_done = FALSE;
    bool node2_done = FALSE;

    if (root == NULL || root2 == NULL) {
        return;
    }

    // Init the stack for iterative traversal.
    stack_head_t s;
    stack_init(&s);

    stack_head_t s2;
    stack_init(&s2);

    while (TRUE) {
        while (temp) {
            push(&s, temp);
            temp = temp->left;
        }

        while (temp2) {
            push(&s2, temp2);
            temp2 = temp2->left;
        }

        if (stack_is_empty(&s) || stack_is_empty(&s2)) {
            // done
            break;
        }

        temp = (struct bst*)pop(&s);
        temp2 = (struct bst*)pop(&s2);

		if (temp->data == temp2->data) {
        	printf("%d ", temp->data);
        	temp = temp->right;
        	temp2 = temp2->right;
		} else if (temp->data < temp2->data) {
        	temp = temp->right;
            push(&s2, temp2);
			temp2 = NULL;
		} else {
        	temp2 = temp2->right;
            push(&s, temp);
			temp2 = NULL;
		}
    }

	// Empty the stack if something is pending.
    while (!stack_is_empty(&s)) {
		pop(&s);
	}

    while (!stack_is_empty(&s2)) {
		pop(&s2);
	}

    // un-init the stack
    stack_uninit(&s2);
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

	printf("Inorder Traversal Tree1\n");
	bst_walk_inorder(root);
	printf("\n");

	printf("Inorder Traversal Tree2\n");
	bst_walk_inorder(root2);
	printf("\n");
	// print the common nodes in the two trees.
	//
	printf("Intresection: \n");
	bst_intersection(root, root2);
	printf("\n");

	printf("Intresection2: \n");
	bst_intersection2(root, root2);
	printf("\n");

	return 0;
}
