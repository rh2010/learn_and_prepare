#include "sorting.h"

using namespace std;

class merge_sort : public base_sort {
	public:
	// Constructor
	merge_sort(int size)
			 : base_sort(size) {
	}

	// Destructor
	virtual ~merge_sort() {
	}

	void merge(int start, int mid, int end) {

		vector<int> aux(end-start+1);

		int p = start;	
		for (int i = 0; p <= end; ++p, ++i) {
			aux[i] = arr[p];
		}

		int i = 0;
		int j = (mid-start)+1;
		for (int k = start; k <= end; ++k) {
			++arr_compares;
			if (i > mid-start) {
				arr[k] = aux[j++];
			} else if (j > end-start) {
				arr[k] = aux[i++];
			} else if (aux[i] < aux[j]) {
				arr[k] = aux[i++];
			} else {
				arr[k] = aux[j++];
			}
		}
	}

	void mergesort(int start, int end) {
		// base case
		if (start >= end) {
			return;
		}

		// find the mid
		int mid = start + (end-start)/2;

		mergesort(start, mid);
		mergesort(mid+1, end);

		merge(start, mid, end);
	}

	// implements merge sort
	void sort_impl() {
		arr_compares = 0;
		cout << arr.size() << endl;
		mergesort(0, size_-1);
	}
};

int main(int argc, char **argv)
{
	if (argc < 2) {
		cout << "usage: ./sort <arr-size>" << endl;
		exit(-1);
	}

	int size = atoi(argv[1]);

	merge_sort test(size);
	test.sort();

	string res = (test.compare())?"Pass":"Fail";

	cout << "Result: " << res << endl;
}
