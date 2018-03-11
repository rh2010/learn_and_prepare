#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
/*
const int max_val = 52;

inline
int r_sides()
{
	return (rand() % max_val);
}

char
get_new_vertex_value(void)
{
	int rand_val = r_sides();
	char val;

	if (rand_val < 26) {
		cout << "Upper ";
		val = static_cast<char>('A' + rand_val);
	} else {
		cout << "Lower ";
		val = static_cast<char>('a' + (rand_val - 26));
	}
	cout << ": " << rand_val << "-> " << val << endl;

	return val;
}

int
main (void)
{
	const int n_dice = 2;
	int d1, d2;

	// set the seed for rand()
	srand(clock());

	cout << "A + 0 -> " << static_cast<char>('A' + 0) << endl;
	cout << "A + 1 -> " << static_cast<char>('A' + 1) << endl;
	cout << "A + 2 -> " << static_cast<char>('A' + 25) << endl;
	cout << "a + 0 -> " << static_cast<char>('a' + 0) << endl;
	cout << "a + 1 -> " << static_cast<char>('a' + 1) << endl;
	cout << "a + 2 -> " << static_cast<char>('a' + 25) << endl;


	cout << "\nEnter the number of trials: ";

	int trials;
	cin >> trials;


	for (int j = 0; j < trials; ++j) {
		get_new_vertex_value();
	}

	return (0);
}*/

double
prob(void)
{
	return (static_cast<double>(rand())/RAND_MAX);
}

int
main(void)
{
	int i = 9, j = 3;
	int edge_density = 45;
	double ed;
	
	cout << "I is "<< i << ", J is " << j << endl;

	{
		int i = j + 2;
		cout << "I is "<< i << ", J is " << j << endl;
	}
	cout << "I is "<< i << ", J is " << j << endl;


	srand(time(0));

	// random probability generation
	for (i = 0; i < 10; i++) {
		cout << prob() << ", ";
	}
	cout << endl;

	ed = static_cast<double>(edge_density / 100);
	cout << "ed1: " << ed << endl;
	ed = (static_cast<double>(edge_density) / 100);
	cout << "ed2: " << ed << endl;
	return (0);
}

