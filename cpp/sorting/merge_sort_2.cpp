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

	void merge(vector<int>& aux, int start, int mid, int end) {
        if (start >= end) {
            return;
        }

        // copy into aux
        for (int i = start; i <= end; ++i) {
            aux[i] = arr[i];
        }

        int i = start;
        int j = mid+1;

        for (int k = start; k <= end; ++k) {
            if (i > mid) {
                arr[k] = aux[j++];
            } else if (j > end) {
                arr[k] = aux[i++];
            } else if (aux[j] < aux[i]) {
                arr[k] = aux[j++];
            } else {
                // stable sort
                arr[k] = aux[i++];
            }
        }
	}

	void mergesort(vector<int>& aux, int start, int end) {
        // keep doubling the bucket size.
        for (int bucket_size = 1; bucket_size < end; bucket_size *= 2) {
            //for (int i = 0; (i <= end) && (((i+bucket_size)-1) < end); i += (2*bucket_size)) {
            for (int i = 0; i < ((end+1)-bucket_size) ; i += (2*bucket_size)) {
                merge(aux, i, ((i + bucket_size)-1), min(end, (i+(2*bucket_size)-1)));
            }
        }
	}

	// implements merge sort
	void sort_impl() {

        // Use an auxiliary array of the same size as of the array
        // to be sorted.
        // Pass around this auxiliary array.
        // This will prevent allocation and de-allocation of aux
        // memory in each function call.
		vector<int> aux;
		aux.reserve(arr.size());
		mergesort(aux, 0, arr.size()-1);
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
