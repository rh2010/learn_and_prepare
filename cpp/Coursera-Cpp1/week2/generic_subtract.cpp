#include <iostream>

using namespace std;

// C++ Generic Subtract  an Array
//
template <class subtractable>
// subtractable is the type here.
//
// s =0 ==> this is the default value.
subtractable subtract(const subtractable data[], int size, subtractable s = 0)
{
	for (int i = 0; i < size; ++i)
		s -= data[i]; // Note: +- must work for subtract
	return s;
}

int
main()
{
	int a[] = {1, 2, 3};
	double b[] = {2.1, 2.2, 2.3};

	cout << "Testing template for sum" << endl;
	cout << subtract(a, 3) << endl;
	cout << subtract(b, 3) << endl;

	return 0;
}
