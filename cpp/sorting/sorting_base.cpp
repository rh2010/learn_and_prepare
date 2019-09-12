#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

class base_sort {
	protected:
		vector<int> arr;
		vector<int> data;
		int size_;
		bool naive_sorted;

		// Implements a naive sort algorithm.
		void naive_sort();

		// show metrics information
		void print_stats();

		// dump the array
		void print_arr();

		// dump the naive algo array
		void print_data();

		// Metrics and counters
		int arr_swaps;
		int data_swaps;

	public:
		// Constructor	
		base_sort(int size)
				  : size_(size)
				  , naive_sorted(false)
				  , arr_swaps(0)
				  , data_swaps(0) {
			cout << "Ctor" << endl;
			arr.reserve(size_);
			data.reserve(size_);
			
			// set the seed for rand()
			srand(clock());
			
			cout << "Arr (" << size << ")" << endl;
			for (int i = 0; i < size_; ++i ) {
				arr[i] = rand()%113;
				data[i] = arr[i];
				cout << arr[i] << " ";
			}
			cout << endl;
		}

		// Destructor
		virtual ~base_sort() {
			print_stats();
			cout << "Dtor" << endl;
		}

		// Compare the result of the sort algorithm with the
		// result from a naive sort algorithm.
		//
		// This check if the sort algorithm is actually working
		// or not.
		bool compare();

		void swap(int idx1, int idx2);

		void naive_swap(int idx1, int idx2);
		// To be implemented by the deriving classes.
		//virtual void sort() = 0;
};

void
base_sort::print_arr() {
	cout << "Arr (" << size_ << ")" << endl;
	for (int i = 0; i < size_; ++i ) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void
base_sort::print_data() {
	cout << "Data (" << size_ << ")" << endl;
	for (int i = 0; i < size_; ++i ) {
		cout << data[i] << " ";
	}
	cout << endl;
}

void
base_sort::print_stats() {
	cout << "Stats:" << endl;

	cout << "Array:" << endl;
	cout << "size:" << size_ << endl;
	cout << "swaps:" << arr_swaps << endl;
	print_arr();

	cout << "Data:" << endl;
	cout << "size:" << size_ << endl;
	cout << "swaps:" << data_swaps << endl;
	print_data();
}

void
base_sort::naive_swap(int i, int j) {
	int temp = data[i];
	data[i] = data[j];
	data[j] = temp;
	++data_swaps;
}

void
base_sort::swap(int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
	++arr_swaps;
}

bool
base_sort::compare() {
	if (!naive_sorted) {
		naive_sort();
		naive_sorted = true;
	}

	for (int i = 0; i < size_; ++i) {
		if (arr[i] != data[i]) return false;
	}

	return true;
}

void
base_sort::naive_sort() {

	for (int i = 0; i < size_-1; ++i) {
		for (int j = 0; j < size_-i; ++j) {
			if (data[j] < data[j-1]) {
				naive_swap(j, j-1);
			}
		}
	}
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		cout << "usage: ./sort <arr-size>" << endl;
		exit(-1);
	}

	int size = atoi(argv[1]);

	base_sort s(size);

	string res = (s.compare())?"Pass":"Fail";

	cout << res << endl;
}
