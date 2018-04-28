#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

/*
 * Read a tree from a file and builds an in-memory tree.
 * The following three traversals are implemented:
 * 	- inorder
 * 	- pre-order
 * 	- post-order
 */
class tree {

	struct node {
		int key;
		int size; // for order statistics
		int height; // for Balancing

		struct node *parent;
		struct node *left;
		struct node *right;

		node (int key)
		:key(key),
		size(0),
		height(0),
		parent(NULL),
		left(NULL),
		right(NULL)
		{
		}
	};

	struct node *root;
	node* do_insert(node* node, int key);
	//node* do_find(node* node, int& key);
	void do_remove(node* node, int key);

	void
	add_left_child(node* p, int key)
	{
		assert(p != NULL);

		node *l = new node(key);

		p->left = l;
		l->parent = p;
	}

	void
	add_right_child(node* p, int key)
	{
		assert(p != NULL);

		node *r = new node(key);

		p->right = r;
		r->parent = p;
	}

	node* do_find(node* n, int& key)
	{
		if (n == NULL)
			return NULL;

		if (n->key == key) {
			return n;
		}
		if (key < n->key) {
			return do_find(n->left, key);
		} else {
			return do_find(n->right, key);
		}
		return NULL; // TDB
	}

	node*
	process_line(vector<tuple<int, int, int>>& lines, node* p, int idx)
	{
		int curr, left, right;

		curr = get<0>(lines[idx]);
		left = get<1>(lines[idx]);
		right = get<2>(lines[idx]);

		node* n = new node(curr);
		n->parent = p;

		if (left == -1) {
			n->left = NULL;
		} else {
			n->left = process_line(lines, n, left);
		}

		if (right == -1) {
			n->right = NULL;
		} else {
			n->right = process_line(lines, n, right);
		}

		return n;
	}

	void
	do_inorder(node* n)
	{
		if (n == NULL) return;

		do_inorder(n->left);
		cout << n->key << " ";
		do_inorder(n->right);
	}

	void
	do_preorder(node* n)
	{
		if (n == NULL) return;

		cout << n->key << " ";
		do_preorder(n->left);
		do_preorder(n->right);
	}

	void
	do_postorder(node* n)
	{
		if (n == NULL) return;

		do_postorder(n->left);
		do_postorder(n->right);
		cout << n->key << " ";
	}

	void
	build_bst_from_file(char *fn)
	{
		assert(fn != NULL);
		cout << "Building tree from file " << fn << endl;

		// open the file to read
		ifstream tree_file(fn);

		// get number of lines
		int vertices; // number of rows
		tree_file >> vertices;
		
		cout << "Total nodes in tree: " << vertices << endl;

		// build the tree
		int n, l, r;
		vector<tuple<int, int, int>> lines;

		for (int i = 0; i < vertices; i++) {
			tree_file >> n >> l >> r;
			lines.push_back(make_tuple(n, l, r));
			cout << "line " << n << " " << l << " " << r << endl;
		}

		// add the root node
		root = process_line(lines, root, 0);
		//new node(get<0>(lines[0]));
		assert(root != NULL);
		assert(root->parent == NULL);
		assert(root->key == get<0>(lines[0]));
	}

	public:
		// constructor
		tree(char* filename)
		:root(NULL)
		{
			assert(filename != NULL);

			build_bst_from_file(filename);
		}

		// destructor
		~tree(void)
		{

		}

		void
		insert(int key)
		{
		}

		void
		find(int& key)
		{
		}

		void
		remove(int key)
		{
		}

		void
		split()
		{

		}

		void
		merge()
		{

		}

		void
		inorder(void)
		{
			cout << "InOrder Traversal: \n\t";
			do_inorder(root);
			cout << endl;
		}

		void
		preorder(void)
		{
			cout << "PreOrder Traversal: \n\t";
			do_preorder(root);
			cout << endl;
		}
		void
		postorder(void)
		{
			cout << "PostOrder Traversal: \n\t";
			do_postorder(root);
			cout << endl;
		}
};

int
main(int argc, char **argv)
{

	if (argc != 2) {
		cout << "usage: ./bst <file-name>" << endl;
		exit (-1);
	}

	char *filename = argv[1];

	tree splay_tree(filename);

	splay_tree.inorder();
	splay_tree.preorder();
	splay_tree.postorder();

	return (0);
}
