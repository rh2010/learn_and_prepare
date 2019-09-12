#include "sorting.h"

using namespace std;

class selection_sort : public base_sort {
	public:
	// Constructor
	selection_sort(int size)
			 : base_sort(size) {
	}

	// Destructor
	virtual ~selection_sort() {
	}

	// implements selection sort
	void sort_impl() {
		arr_compares = 0;

		for (int i = 0; i < size_; ++i) {
			int min = i; // min index

			for (int j=i; j < size_; ++j) {
				++arr_compares;
				if (arr[j] < arr[min]) {
					min = j;
				}
			}
			if (i != min) {
				swap(i, min);
			}
		}
	}
};

int main(int argc, char **argv)
{
	if (argc < 2) {
		cout << "usage: ./sort <arr-size>" << endl;
		exit(-1);
	}

	int size = atoi(argv[1]);

	selection_sort test(size);
	test.sort();

	string res = (test.compare())?"Pass":"Fail";

	cout << "Result: " << res << endl;
}
