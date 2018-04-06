#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector> // vector
#include <queue> // priority queue
#include <ctime> // time()

using namespace std;

static int const range = 1000;

// A comparator class to implement min heap
class min_heap {
	public:
	// overload()
	bool operator()(const int& a, const int& b)
	{
		return (a > b);
	}
};

// heap of the lower half of the elements
//
// by default priority_queue is a max_heap.
priority_queue<int> heap_low;

// heap of the high half of the elements.
priority_queue<int, vector<int>, min_heap> heap_high;

double
get_median(int element)
{
	double median = -1;

	// base case
	if (heap_high.empty()) {
		// First emement
		median = element;
		heap_high.push(element);
		return median;
	}

	int size_heap_low;
	int size_heap_high;

	if (element < heap_high.top()) {
		cout << "Adding to heap_low" << endl;
		// put in heap_low
		heap_low.push(element);

		size_heap_low = heap_low.size();
		size_heap_high = heap_high.size();
	
		// Since, we have added in heap_low, the size of heap_low
		// can be greater or equal to heap_high, it can't be less.
		//
		// Since, we maintain a size difference of 1 at all times.
		if (size_heap_low > size_heap_high) {

			// if the difference is more than one, then, do the rebalance.
			if (size_heap_low - size_heap_high > 1) {
				heap_high.push(heap_low.top());

				//remove the element from heap_low
				heap_low.pop();
				assert(heap_low.size() == heap_high.size());
			} else {
				median = heap_low.top();
			}
		} else {
			assert(size_heap_low == size_heap_high);
		}
	} else {
		// put in heap_high
		heap_high.push(element);

		size_heap_low = heap_low.size();
		size_heap_high = heap_high.size();

		// Since, we have added in heap_high, the size of heap_high
		// can be greater or equal to heap_low, it can't be less.
		//
		// Since, we maintain a size difference of 1 at all times.
		if (size_heap_high > size_heap_low) {
			
			// if the difference is more than one, then, do the rebalance.
			if (size_heap_high - size_heap_low > 1) {
				cout << "Rebalance\n";
				heap_low.push(heap_high.top());

				// remove the element from heap_high
				heap_high.pop();
				assert(heap_low.size() == heap_high.size());
			} else {
				median = heap_high.top();
			}
		} else {
			assert(size_heap_low == size_heap_high);
		}
	}

	if (heap_low.size() == heap_high.size()) {
		median = (heap_high.top() + heap_low.top() ) / 2;
	}

	assert(median != -1);
	return median;
}

int
main(int argc, char **argv)
{
	if (argc != 2) {
		cout << "Usage: ./a.out <Max Size of the Stream>" << endl;
		return (-1);
	}

	int size = atoi(argv[1]);
	vector<int> stream;
	stream.reserve(size);

	srand(time(0));
	int element;

	cout << "Stream: \n\t";
	// randomly initialize the stream
	for (int i=0; i<size; i++) {
		element = rand() % 1000;
		stream.push_back(element);
		cout << element << " ";
	}
	cout << endl;

	for (auto it = stream.begin(); it != stream.end(); it++) {
		cout << "Median: " << get_median(*it) << endl;
	}
}
