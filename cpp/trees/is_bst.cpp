#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

/*
 * The harder version of checking if a given tree is BST or not.
 * The harder version deals with keys with equal values.
 */
struct Node {
  long int key;
  int left;
  int right;
  int max;
  bool max_present;
  int min;
  bool min_present;

  Node() : key(0), left(-1), right(-1), max(0), min(0), min_present(false), max_present(false) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_), max(0), min(0), min_present(false), max_present(false) {}

  public:
};
vector<Node> tree;

inline int
get_min(vector<Node>& t, int idx)
{
	assert(idx != -1);

	if (t[idx].left == -1) {
		return t[idx].key;
	}

	if (t[idx].min_present == false) {
		t[idx].min = get_min(t, t[idx].left);
		t[idx].min_present = true;
	}

	//int temp_idx = idx;
	//while (t[temp_idx].left != -1) {
	//	temp_idx = t[temp_idx].left;
	//}
	//t[idx].min = t[temp_idx].key;
	//t[idx].min_present = true;

	return t[idx].min;
}

inline int
get_max(vector<Node>& t, int idx)
{
	assert(idx != -1);

	if (t[idx].right == -1) {
		return t[idx].key;
	}

	if (t[idx].max_present == false) {
		t[idx].max = get_max(t, t[idx].right);
		t[idx].max_present = true;
	}

	//int temp_idx = idx;
	//while (t[temp_idx].right != -1) {
	//	temp_idx = t[temp_idx].right;
	//}
	//t[idx].max = t[temp_idx].key;
	//t[idx].max_present = true;

	return t[idx].max;
}

bool
isBST3(vector<Node>& t, int idx)
{
	if (idx == -1) return true;
	if (t.size() == idx) return true;

	int key = t[idx].key;
	int l = t[idx].left;

	if ((t[idx].left != -1) &&
		((get_min(t, t[idx].left) >= key) ||
		(get_max(t, t[idx].left) >= key))) {
		return false;
	}

	if ((t[idx].right != -1) &&
		((get_min(t, t[idx].right) < key) ||
		(get_max(t, t[idx].right) < key))) {
		return false;
	}

	return (isBST3(t, t[idx].left) && isBST3(t, t[idx].right));
}

bool
isBST2(vector<Node>& t, int idx, int& prev_max)
{
	if (idx == -1) return true;
	if (t.size() == idx) return true;

	if (!isBST2(t, t[idx].left, prev_max)) {
		return false;
	}

	int key = t[idx].key;
	if (key < prev_max) {
		return false;
	}
	prev_max = key;

	return isBST2(t, t[idx].right, prev_max);
}

/*
 * min - the minimum value the node.key can take
 * max - the maximum vale the node.key can take
 * idx - index into the vector for the current node
 */
bool
isBST(vector<Node>& t, long int min, long int max, int idx)
{
	if (idx == -1) return true;
	if (t.size() == idx) return true;
	
	int key = t[idx].key;

	//if ((key < min) || (key > max)) {
	//	return false;
	//}
	if (!(min < key) || !(key <= max)) {
		return false;
	}
	return (isBST(t, min, key-1, t[idx].left) &&
		   isBST(t, key+1, max, t[idx].right));
}
/*
 * Perform an inorder traversal and keep building a list in the
 * in-order traversal order.
 * At each node, before going right, we know the value of the left
 * child as well, so, we can check the value of the left child should be
 * strictly smaller than it's parent. However, the value of the right child
 * can be greater than or equal to a node.
 */
bool
in_order(vector<Node>& t, int idx, vector<int>& res)
{
	bool l = true;
	bool r = true;

	if (t[idx].left != -1) {
		if (t[t[idx].left].key >= t[idx].key) {
			return false;
		}
		l = in_order(t, t[idx].left, res);
	}

	if ((res.size() > 0) && (res.back() > t[idx].key)) {
		return false;
	}

	res.push_back(t[idx].key);

	if (t[idx].right != -1) {
		if (t[t[idx].right].key < t[idx].key) {
			return false;
		}
		r = in_order(t, t[idx].right, res);
	}
	return (l && r);
}

/*
 * This version works properly for huge data sets and is the fastest amongst all the versions.
 */
bool
isBST4(vector<Node>& t, int idx)
{
	if (t.size() == idx) return true;
	vector<int> result;

	return in_order(t, idx, result);
}

bool IsBinarySearchTree(vector<Node>& tree) {
  // Implement correct algorithm here
  //return isBST(tree, LLONG_MIN, LLONG_MAX, 0);
  //int min = INT_MIN;
  //return isBST2(tree, 0, min);
  //return isBST3(tree, 0);
  return isBST4(tree, 0);
}

int main() {
  int nodes;
  cin >> nodes;
  tree.reserve(nodes);

  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
