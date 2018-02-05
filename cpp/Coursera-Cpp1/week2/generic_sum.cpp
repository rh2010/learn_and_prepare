#include <iostream>

using namespace std;

// C++ Generic Sum an Array
//
template <class summable>
// summable is the type here.
//
// s =0 ==> this is the default value.
summable sum(const summable data[], int size, summable s = 0)
{
	for (int i = 0; i < size; ++i)
		s += data[i]; // Note: += must work for summable
	return s;
}

int
main()
{
	int a[] = {1, 2, 3};
	double b[] = {2.1, 2.2, 2.3};

	cout << "Testing template for sum" << endl;
	cout << sum(a, 3) << endl;
	cout << sum(b, 3) << endl;

	return 0;
}
