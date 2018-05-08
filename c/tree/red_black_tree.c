#include "../util.h"
#include "queue.h"

#define LCHILD(x)	((x)->left)
#define RCHILD(x)	((x)->right)
#define HEIGHT(x)	((x) ? (x)->height : 0)

/*
 * An implementation of the LLRB Tree (Left Leaning Red Black Tree), which
 * corresponds to the 2-3 Tree.
 */

/*
 * Invariants of a Red-Black Tree
 *	- All NULL links have Black Color
 *	- The tree is perfectly balanced for the Black-Height of the tree i.e.
 *	  from the root node to any leaf, the path has the same number of
 *	  Black-Nodes.
 *  - GOAL: Maintain perfect Black Balance.
 */
/*
 * Implement the following operations for a red-black-tree.
 * 	- Insertion
 * 	- Deletion
 * 	- Find
 * 	- Display
 */
struct rb_node {
	int key;
	int value;
	struct rb_node *left;
	struct rb_node *right;
	//struct rb_node *parent; // Not using parent!
	int size;
	bool color;
};

struct rb_node *rb_root;

#define RED TRUE
#define BLACK FALSE

// is the node red
// TRUE -> Red
// FALSE -> Black
bool isRed(struct rb_node *node);

// initialize the rb-tree
bool rb_tree_init();

// un-initialize the rb-tree
bool rb_tree_uninit();

// returns the size of the rb_tree
int rb_size(struct rb_node *root);

// is the rb-tree empty
bool rb_is_empty(struct rb_node *root);

// add a node
//
// a.k.a put(key, value), in key-value terms.
struct rb_node* rb_add(struct rb_node *root, int key, int value);

// The actual worker to add a new node in the tree.
struct rb_node* rb_add_node(struct rb_node *root, int key, int value);

// find a node
//
// a.k.a get(key),
// given a key find the value associated with it.
struct rb_node* rb_find(struct rb_node *root, int key);

// delete
//
// given a key remove the value associated with it or remove the
// complete entry from the tree.
struct rb_node*  rb_delete(struct rb_node *root, int key);

// perform a level-order traversal
void rb_level_order(struct rb_node *root);

// perform an in-order traversal
void rb_inorder(struct rb_node *root);

// rank
//
// what is the rank of the given node with 'key'
int rb_rank(struct rb_node *root, int key);

// select
//
// select the node with 'rank'
int rb_select(struct rb_node *root, int rank);

// Left Rotate
struct rb_node* rb_rotate_left(struct rb_node* root);

// Right Rotate
struct rb_node* rb_rotate_right(struct rb_node* root);

struct rb_node*
rb_rotate_left(struct rb_node* root)
{
	struct rb_node* r;
	assert(root != NULL);

	r = root->right;

	assert(isRed(r));

	root->right = r->left;
	r->left = root;
	r->color = root->color;
	root->color = RED;

	// fix the size.
	root->size = rb_size(root->left) + 1 + rb_size(root->right);
	return r;
}

struct rb_node*
rb_rotate_right(struct rb_node* root)
{
	struct rb_node* l;

	assert(root != NULL);

	l = root->left;

	assert(isRed(l));

	root->left = l->right;
	l->right = root;
	l->color = root->color;
	root->color = RED;

	// fix the size.
	root->size = rb_size(root->left) + 1 + rb_size(root->right);
	return l;
}

/*
 * At the 'node' flip colors of:
 * 	the node
 * 	the left child
 * 	the right child
 *
 * 	This is called only when both the children have 
 * 	RED colors.
 */
void
rb_flip_colors(struct rb_node* node)
{
	assert(node != NULL);
	assert(!isRed(node));
	assert(isRed(node->left));
	assert(isRed(node->right));

	node->color = RED;
	node->left->color = BLACK;
	node->right->color = BLACK;
}


bool
isRed(struct rb_node *node)
{
	if (node == NULL) return FALSE;

	return (node->color == RED);
}

int
rb_size(struct rb_node *root)
{
	if (root == NULL) {
		return 0;
	}
	return root->size;
}

bool
rb_is_empty(struct rb_node *root)
{
	return (root == NULL);
}

struct rb_node*
rb_get_new_node(int key, int value)
{
	struct rb_node* new;

	new = (struct rb_node*)malloc(sizeof (struct rb_node));
	if (new == NULL) {
		printf("Error: Unable to allocate memory for new rb_node\n");
		return NULL;
	}

	new->color = RED;
	new->key = key;
	new->value = value; // for now the key and value is same
	new->left = NULL;
	new->right = NULL;
	new->size = 0;

}

struct rb_node*
rb_add(struct rb_node* root, int key, int value)
{
	root = rb_add_node(root, key, value);

	// 'root' is the new root of the tree
	// the color should be black.
	root->color = BLACK;
}

struct rb_node*
rb_add_node(struct rb_node* root, int key, int value)
{
	if (root == NULL) {
		return rb_get_new_node(key, value);
	}

	if (key == root->key) {
		// key already present, just update the value
		root->value = value;
		return root;
	} else if (key < root->key) {
		// add in the left sub-tree
		root->left = rb_add_node(root->left, key, value);
	} else {
		// add in the right sub-tree
		root->right = rb_add_node(root->right, key, value);
	}
	printf("At %d [%c]\n", root->value, isRed(root)?'r':'b');
	// check if rebalance needed.
	if (!isRed(root->left) && isRed(root->right)) {
		printf("Left Rotate\t");
		root = rb_rotate_left(root);
	}
	if (isRed(root->left) && ((root->left != NULL) && isRed(root->left->left))) {
		printf("Right Rotate\t");
		root = rb_rotate_right(root);
	}
	if (isRed(root->left) && isRed(root->right)) {
		printf("Flip Colors");
		rb_flip_colors(root);
	}
	printf("\n");

	// adjust the size
	root->size = rb_size(root->left) + 1 + rb_size(root->right);
	return root;
}

struct rb_node*
rb_find(struct rb_node *root, int key)
{
	struct rb_node* result = NULL;

	if (root == NULL) {
		return NULL;
	}

	while (root != NULL) {
		if (root->key == key) {
			result = root;
			break;
		}
		if (key < root->key) {
			// go left
			root = root->left;
		} else {
			// go right
			root = root->right;
		}
	}
	return result;
}

struct rb_node*
rb_delete(struct rb_node *root, int key)
{
	return NULL;
}

void
rb_level_order(struct rb_node *root)
{
	queue_head_t q;
	queue_head_t *queue;
	struct rb_node* temp;
	int level, level_size;

	queue = &q;

	if (root == NULL) {
		return;
	}

	queue_init(queue);

	// the traversal starts from the root node.
	enqueue(queue, root);
	level = 0;
	level_size = 0;

	while (queue_size(queue) > 0) {
		level++;
		level_size = queue_size(queue);

		printf("Level: %d\t", level);
		while (level_size > 0) {
			temp = (struct rb_node*)dequeue(queue);
			assert(temp != NULL);
			printf("%d [%c]  ", temp->value, isRed(temp)?'r':'b');

			if (temp->left) {
				enqueue(queue, temp->left);
			}
			if (temp->right) {
				enqueue(queue, temp->right);
			}
			level_size--;

		} // level
		printf("\n");

	}
	queue_uninit(queue);

	return;
}

/*
 * Iterative In-order traversal.
 */
void
rb_inorder(struct rb_node *root)
{
	struct rb_node* temp;
	stack_head_t s;
	stack_head_t* stack;
	bool done = FALSE;

	if (root == NULL) {
		return;
	}
	stack = &s;
	stack_init(stack);

	temp = root;

	while(!done) {
		if (temp != NULL) {
			push(stack, temp);
			temp = temp->left;
		} else {
			// temp == NULL
			if (!stack_is_empty(stack)) {
				temp = (struct rb_node*)pop(stack);
				printf("%d ", temp->value);
				temp = temp->right;
			} else {
				// stack is empty
				// all done
				done = TRUE;
			}
		}
	} // while
}

int
rb_rank(struct rb_node *root, int key)
{
	return 0;
}

int
rb_select(struct rb_node *root, int rank)
{
	return 0;
}

int
main(int argc, char **argv)
{
	int count = 0;
	int i;
	int key;
	int rank;
	struct rb_node* temp;
	//int arr[10];
	int choice = 0;

	if (argc <= 3) {
		printf("Too few params\n");
		printf("usage: ./rb_tree <count of elements> <count number of elements>");
		exit(-1);
	}
	count = atoi(argv[1]);

	if (argc != (count+2)) {
		printf("Wrong count of elements, should be: %d, given: %d\n", count,
			   (argc-2));
		exit(-1);
	}

	// Create the root node.
	rb_root = rb_add(rb_root, atoi((argv[2])), atoi((argv[2])));
	if (rb_root == NULL) {
		printf("Can't create root node\n");
		exit(-1);
	}
	// Root's color is always Black
	rb_root->color = BLACK;

	// populate the rest of the tree.
	for (i=0; i < (count-1); i++) {
		printf("[%d] Adding node %d\n", i, atoi(argv[i+3]));
		rb_root = rb_add(rb_root, atoi(argv[i+3]), atoi(argv[i+3]));
		if (rb_root == NULL) {
			printf("Can't add a new node to the tree\n");
			printf("Only %d nodes were added\n", i+1);
			exit(-1);
		}
		rb_level_order(rb_root);
	}
	printf("Added %d nodes\n", i+1);

	// print the tree in in-order
	//
	printf("Inorder Traversal: \n");
	rb_inorder(rb_root);
	printf("\n");
	// print the tree in pre-order
	//
	printf("Level Order Traversal: \n");
	rb_level_order(rb_root);
	printf("\n");

	while(1) {
		printf("1) Insert\n2) Inorder\n3) Level-order\n4) Rank\n5) Select\n6)Exit\nChoice: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1: // insert
				printf("key: \n");
				scanf("%d", &i);
				temp = rb_add(rb_root, i, i);
				if (temp == NULL) {
					printf("Can't add a new node to the tree\n");
					printf("Only %d nodes were added\n", i+1);
					exit(-1);
				}
				break;
			case 2: // in order traversal
				rb_inorder(rb_root);
				printf("\n");
				break;
			case 3: // level order traversal
				rb_level_order(rb_root);
				printf("\n");
				break;
			case 4: // rank
				printf("key: \n");
				scanf("%d", &key);
				i = rb_rank(rb_root, key);
				printf("%d\n", i);
				break;
			case 5: // select
				printf("key: \n");
				scanf("%d", &rank);
				key = rb_select(rb_root, rank);
				printf("%d\n", key);
				break;
			case 6:
				exit(0);
				break;
			default:
				printf("\n");
				break;
		}
	}

	return 0;
}
