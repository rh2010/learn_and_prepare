/*
 * Cpp program to sum 'N' numbers.
 */
#include <iostream>
#include <vector>

using namespace std;

const int N = 40; // global 

//
//TODO: Use iterators
//
// int &p => It is used as called by reference here.
void inline
sum(int &p,  int n, vector<int> d)
{
	p = 0;

	for (int i = 0; i < n; ++i)
		p = p + d.at(i);

	cout << "Sum done\n";
}

int
main()
{
	int accum = 0;
	vector<int> data;
	data.reserve(N);

	// initializing the data vector
	cout << "Initializing the data vector\n";
	for (int i = 0; i < N; ++i)
		data.push_back(i);

	cout << "Calling sum\n";
	sum(accum, N, data);

	cout << "Sum is: " << accum << endl;

	return 0;
}
