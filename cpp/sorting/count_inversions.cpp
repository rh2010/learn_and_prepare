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

	unsigned int merge(vector<int>& aux, int start, int mid, int end) {
		// copy to aux
		for (int i = start; i <= end; ++i){
			aux[i] = arr[i];
		}

		int i=start;
		int j=mid+1;
		unsigned int inversions = 0;

		for (int k = start; k <= end; ++k) {
			if (i > mid) {
				arr[k] = aux[j++];
			} else if (j > end) {
				arr[k] = aux[i++];
			} else if (aux[i] < aux[j]) {
				arr[k] = aux[i++];
			} else {
				inversions += (mid+1)-i;
				arr[k] = aux[j++];
			}
		}
		return inversions;
	}

	unsigned int mergesort(vector<int>& aux, int start, int end) {
		if (start >= end) {
			return 0;
		}
		unsigned int inversions = 0;
		int mid = start + (end-start)/2;
		inversions += mergesort(aux, start, mid);
		inversions += mergesort(aux, mid+1, end);
		inversions += merge(aux, start, mid, end);

		return inversions;
	}

	// implements merge sort
	void sort_impl() {
		// TBD
		unsigned int inversions = 0;
		vector<int> aux;
		aux.reserve(arr.size());
		inversions = mergesort(aux, 0, arr.size()-1);
		cout << "Inversions: " << inversions << endl;
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
