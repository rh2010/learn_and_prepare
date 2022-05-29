#include <iostream>
#include <cstdlib>
#include <cstring>
#include <queue>

using namespace::std;

class tree {

	typedef struct node {
		int val;
		int height;

		struct node *left;
		struct node *right;

		node(int v) :
		val(v),
		left(NULL),
		right(NULL),
		height(1)
		{}

	} node_t;

	node_t *root;

	/*
	 * 
	 */
	int
	height(node* root) {
		if (root == NULL) {
			return 0;
		}
		return root->height;
	}

	node*
	left_rotate(node* root) {
		printf("\tLeft Rotation (%d).\n", root->val);
		node *rr = root->right;
		node *rl = root->left;

		root->right = rr->left;
		rr->left = root;

		// re-adjust the height
		root->height = 1 + max(height(root->left), height(root->right));
		rr->height = 1 + max(height(rr->left), height(rr->right));
		
		return rr;
	}

	node*
	right_rotate(node* root) {
		printf("\tRight Rotation (%d).\n", root->val);
		node *rr = root->right;
		node *rl = root->left;
		node *r = root;

		root->left = rl->right;
		rl->right = root;

		// re-adjust the height
		root->height = 1 + max(height(root->left), height(root->right));
		rl->height = 1 + max(height(rl->left), height(rl->right));

		return rl;
	}

	node*
	add(node* root, int v) {
		if (root == NULL) {
			return new node(v);
		}

		if (v < root->val) {
			root->left = add(root->left, v);
		} else {
			root->right = add(root->right, v);
		}

		// adjust the height
		root->height = max(height(root->left), height(root->right)) + 1;

		// balance
		//
		int diff = height(root->left) - height(root->right);
		printf("Diff (%d), %s\n", diff, (abs(diff)>1)?"Re-balance...":"");

	
		if (abs(diff) > 1) {
			level_order_traversal();
			// L-L case
			//
			if (diff > 1 && v < root->left->val) {
				// right rotate on root
				return right_rotate(root);
			}

			// L-R case
			//
			if (diff > 1 && v > root->left->val) {
				// first left rotate root->left
				//
				root->left = left_rotate(root->left);
				return right_rotate(root);
				// 2nd right rotate root
			}
			// R-R case
			//
			if (diff < -1 && v > root->right->val) {
				// left rotate on root
				return left_rotate(root);
			}
			// R-L case
			//
			if (diff < -1 && v < root->right->val) {
				// right rotate on root->right
				root->right = right_rotate(root->right);
				// left rotate on root
				return left_rotate(root);
			}
		}

		// return
		return root;
	}

	node*
	find(node* n, int v) {
		if (n == NULL) {
			return NULL;
		}

		if (v == n->val) {
			return n;
		} else if (v < n->val) {
			return find(n->left, v);
		} else {
			return find(n->right, v);
		}
	}

	public:

		// default constructor
		tree() :
		root(NULL) {
		}

		void
		insert(int v)
		{
			printf("Insert (%d) \n", v);
			if (root == NULL) {
				root = new node(v);
				return;
			}
			root = add(root, v);
		}

		int
		del(int v)
		{
			return v;
		}
		
		bool
		find(int v)
		{
			node* n = find(root, v);
			if (n == NULL) return false;

			return true;
		}

		void
		inorder(void)
		{
		}

		void
		level_order_traversal(void)
		{
			printf("Level order traversal:\n");
			if (root == NULL) {
				printf("\tempty tree\n");
				return;
			}

			queue<node*> q;
			q.push(root);

			int count;
			int level = 0;
			while(!q.empty()) {
				count = q.size();

				node *t;
				printf("[%d]", level++);
				while (count-- > 0) {
					t = q.front();
					q.pop();

					printf("\t(%d, %d)", t->val, t->height);

					if (t->left) q.push(t->left);
					if (t->right) q.push(t->right);
				}
				printf("\n");
			}
		}
};

int main(void)
{
	tree t;

	t.insert(4);
	t.level_order_traversal();
	t.insert(3);
	t.level_order_traversal();
	t.insert(2);
	t.level_order_traversal();
	t.insert(1);
	t.level_order_traversal();
	t.insert(0);
	t.level_order_traversal();
	t.insert(9);
	t.level_order_traversal();
	t.insert(8);
	t.level_order_traversal();
	t.insert(11);
	t.level_order_traversal();

	printf("Search(4) - %s.\n", t.find(4)?"Found":"Not found");
	printf("Search(3) - %s.\n", t.find(4)?"Found":"Not found");
	printf("Search(2) - %s.\n", t.find(4)?"Found":"Not found");
}
