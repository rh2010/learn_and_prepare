#ifndef _SORTING_BASE_H_
#define _SORTING_BASE_H_
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <chrono>

using namespace std;
using namespace chrono;

#define PRIME_NUM 2887

class base_sort {
	protected:
		vector<int> arr;
		vector<int> data;
		int size_;
		bool naive_sorted;

		// Implements a naive sort algorithm.
		void
		naive_sort() {
			auto start_time = steady_clock::now();
			for (int i = 0; i < size_-1; ++i) {
				for (int j = 1; j < size_-i; ++j) {
					++data_compares;
					if (data[j] < data[j-1]) {
						naive_swap(j, j-1);
					}
				}
			}
			data_time_ms = duration_cast<milliseconds>(steady_clock::now()-start_time);
		}

		// show metrics information
		void
		print_stats() {
			cout << "\nStats:" << endl;
		
			cout << "Array:\n" << endl;
			cout << "\tsize: " << arr.size() << endl;
			cout << "\tswaps: " << arr_swaps << endl;
			cout << "\tcompares: " << arr_compares << endl;
			cout << "\tduration: " << arr_time_ms.count() << endl;
			//print_arr();
		
			cout << "Data:\n" << endl;
			cout << "\tsize: " << data.size() << endl;
			cout << "\tswaps: " << data_swaps << endl;
			cout << "\tcompares: " << data_compares << endl;
			cout << "\tduration: " << data_time_ms.count() << endl;
			//print_data();
		}

		// dump the array
		void
		print_arr() {
			cout << "size (" << size_ << ")" << endl;
			for (int i = 0; i < size_; ++i ) {
				cout << arr[i] << " ";
			}
			cout << endl;
		}

		// dump the naive algo array
		void
		print_data() {
			cout << "size (" << size_ << ")" << endl;
			for (int i = 0; i < size_; ++i ) {
				cout << data[i] << " ";
			}
			cout << endl;
		}

		// Metrics and counters
		int arr_swaps;
		int arr_compares;
		int data_swaps;
		int data_compares;
		milliseconds arr_time_ms;
		milliseconds data_time_ms;

	public:
		// Constructor	
		base_sort(int size)
				  : size_(size)
				  , naive_sorted(false)
				  , arr_swaps(0)
				  , data_swaps(0)
				  , arr_compares(0)
				  , data_compares(0) {
			cout << "base_sort Ctor" << endl;
			arr.reserve(size_);
			data.reserve(size_);
			
			// set the seed for rand()
			srand(clock());
			
			cout << "Arr (" << size << ")" << endl;
			for (int i = 0; i < size_; ++i ) {
				int val = rand() % PRIME_NUM;
				arr.push_back(val);
				data.push_back(val);
				//cout << arr[i] << " ";
			}
			cout << "\n" << endl;
		}

		// Destructor
		virtual ~base_sort() {
			print_stats();
			cout << "base_sort Dtor" << endl;
		}

		// Compare the result of the sort algorithm with the
		// result from a naive sort algorithm.
		//
		// This check if the sort algorithm is actually working
		// or not.
		bool
		compare() {
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
		naive_swap(int i, int j) {
			int temp = data[i];
			data[i] = data[j];
			data[j] = temp;
			++data_swaps;
		}
		
		void
		swap(int i, int j) {
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			++arr_swaps;
		}

		void sort() {
			auto start_time = steady_clock::now();
			sort_impl();
			arr_time_ms = duration_cast<milliseconds>(steady_clock::now()-start_time);
		}

		// To be implemented by the deriving classes.
		virtual void sort_impl() = 0;
};

#endif // _SORTING_BASE_H_
