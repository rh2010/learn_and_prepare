#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

/*
 * Given a unimodal array, find the max, element.
 * A Unimodal array: 
 *  its entries are in increasing order up until its maximum element,
 *  after which its elements are in decreasing order.
 */

int
find_max(const vector<int> a, int left, int right)
{
	int idx_max = -1;
	int s, e;
	int mid;

	s = left;
	e = right;

	while (left <= right) {
		mid = left + (right-left)/2;

		cout << "L: " << left << " R: " << right << " M: " << mid << endl;

		if ((a[mid-1] < a[mid]) && (a[mid] > a[mid+1])) {
			idx_max = mid;
			cout << "found" << endl;
			break;
		} else if ((a[mid-1] < a[mid]) && (a[mid] < a[mid+1])) {
			// go right
			left = mid + 1;
		} else if ((a[mid-1] > a[mid]) && (a[mid] > a[mid+1])) {
			// go left
			right = mid - 1;
		} else {
			assert("Should not be here!");
		}
	}
	if (idx_max == -1 && mid == right) {
		idx_max = right;
	}
	cout << "Done L: " << left << " R: " << right << " M: " << mid << endl;
	cout << "Index: " << idx_max << endl;;
	return a[idx_max];
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
	cout << find_max(a, 0, a.size()-1) << endl;
}
