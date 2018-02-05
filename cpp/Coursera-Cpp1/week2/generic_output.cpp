#include <iostream>

using namespace std;

// C++ Generic List an Array
//
template <class listable>
// listable is the type here.
//
// s =0 ==> this is the default value.
void listg(const listable data[], int size)
{
	for (int i = 0; i < size; ++i)
		cout << data[i] << " ";
	cout << endl;
}

int
main()
{
	int a[] = {1, 2, 3};
	double b[] = {2.1, 2.2, 2.3};

	cout << "Testing template for listing" << endl;
	listg(a, 3);
	listg(b, 3);

	return 0;
}
