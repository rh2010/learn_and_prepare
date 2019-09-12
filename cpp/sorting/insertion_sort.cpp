#include "sorting.h"

using namespace std;

class insertion_sort : public base_sort {
	public:
	// Constructor
	insertion_sort(int size)
			 : base_sort(size) {
	}

	// Destructor
	virtual ~insertion_sort() {
	}

	// implements insertion sort
	void sort_impl() {
		arr_compares = 0;

		for (int i = 1; i < size_; ++i) {
			for (int j=i; j >= 0; --j) {
				++arr_compares;
				if (arr[j] < arr[j-1]) {
					swap(j, j-1);
				} else {
					break;
				}
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

	insertion_sort test(size);
	test.sort();

	string res = (test.compare())?"Pass":"Fail";

	cout << "Result: " << res << endl;
}
