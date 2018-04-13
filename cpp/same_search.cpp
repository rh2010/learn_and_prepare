#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

/*
 * You are given a sorted (from smallest to largest) array A of n distinct
 * integers which can be positive, negative, or zero. You want to decide whether
 * or not there is an index i such that A[i] = i.
 *
 * Design the fastest algorithm that you can for solving this problem.
 */

int
find_same(const vector<int> a, int left, int right)
{
	int index = -1;
	int mid;

	while (left <= right) {
		mid = left + (right-left)/2;

		if (a[mid] == mid) {
			index = mid;
			break;
		} else if (a[mid] > mid) {
			//if (left == mid) {
			//	// not found
			//	break;
			//}
			// check left
			right = mid - 1;
		} else {
			// check right
			left = mid + 1;
		}
	}

	return index;
}

int main()
{
	int n;
	cin >> n; // size of the array

	vector<int> a(n);

	// initialize the array
	for (int i=0; i<a.size(); i++) {
		cin >> a[i];
	}
	int index = find_same(a, 0, a.size()-1);
	if (index == -1) {
		cout << "Not Found!" << endl;
	} else {
		cout << "Found at [" << index << "]" << endl;
	}
}
