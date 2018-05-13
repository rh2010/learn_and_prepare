#include "../util.h"
#include "queue.h"

/*
 * Interval Trees:
 * 	- Interval search trees, stores intervals (lo, hi)
 * 	- Implemented as a regular BST
 * 		- each node is (lo, hi)
 * 		- the key is 'lo' i.e. left endpoint
 * 		- At every node store the Max-End point in the sub-tree
 * 		  rooted at that node.
 *
 *
 * 	- APIs
 * 		void put(Key lo, Key hi, Value value)
 * 			- insert as a regular binary tree
 * 			- when going back up the tree, just update the 
 * 			  new max end point in the path.
 * 		Value get(Key lo, Key hi)
 * 			- Search:
 * 				current = root;
 * 				- if the key intersects the current node
 * 					return current_node
 * 				- else if .. current->left is NULL
 * 					// go right
 * 					current = current->right
 * 				- else if .. current->left->max < lo
 * 					// go right
 * 					current = current->right
 * 				- else
 * 					// go left
 * 					current = current->left
 *
 * 		void delete(Key lo, Key hi)
 * 		list<Value> intersects(Key lo, Key hi)
 * 			- all intervals that intersect the given interval.
 */
struct it_node {
	// keys
	int lo;
	int high;
	int value;
	struct it_node *left;
	struct it_node *right;
	int max;
};//interval tree node

struct it_node *root;

struct it_node*
get_new_node(int key_lo, int key_hi, int value)
{
	struct it_node* new;

	new = (struct it_node*)malloc(sizeof (struct it_node));
	if (new == NULL) {
		printf("Error: Unable to allocate memory for new rb_node\n");
		return NULL;
	}

	new->lo = key_lo;
	new->hi = key_hi;
	new->value = value; // for now the key and value is same
	new->left = NULL;
	new->right = NULL;
	new->max = key_hi;

}

struct it_node_max(struct it_node *node)
{
	if (node == NULL) {
		return 0;
	}
	return node->max;
}

struct it_node*
add_node(struct it_node* root, int key_lo, int key_hi, int value)
{
	if (root == NULL) {
		return get_new_node(key_lo, key_hi, value);
	}

	// not supporting over-lapping ranges.
	if (key_lo == root->lo && key_hi == root->hi ) {
		// key already present, just update the value
		root->value = value;
	} else if (key < root->lo) {
		// add in the left sub-tree
		root->left = add_node(root->left, key_lo, key_hi, value);
	} else {
		// add in the right sub-tree
		root->right = add_node(root->right, key, value);
	}

	// adjust the max
	root->max = MAX(MAX(it_node_max(root->left), it_node_max(root->right)), root->max);

	return root;
}

bool inline
contains(struct it_node *node, int lo, int hi)
{
	assert(node != NULL);

	return ((lo >= node->lo) && (hi <= node->hi));
}

/*
 * Give a range with 'lo' and 'hi' endpoints, find if any of the
 * intervals present overlap with this range.
 */
struct it_node*
find_intersection(struct it_node *root, int lo, int hi)
{
	struct it_node *node;

	node = root;

	while (node != NULL) {
		if (contains(node, lo, hi)) {
			return node;
		} else if (node->left == NULL) {
			// go right
			node = node->right;
		} else if (lo > it_node_max(node->left)) {
			// go right
			node = node->right;
		} else {
			// go left
			node = node->left;
		}
	} // while

	return NULL;
}

struct it_node*
delete_node(struct it_node *root, int lo, int hi)
{
	return NULL;
}
