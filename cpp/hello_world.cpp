#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int sides = 6; // used instead of a sharp define.
					 // 
					 // it is believed that more error are made when using
					 // pre-processor textual substitution.

inline
int r_sides()
{
	return (rand() % (sides + 1));
}

int
main (void)
{
	const int n_dice = 2;
	int d1, d2;

	// set the seed for rand()
	srand(clock());

	cout << "\nEnter the number of trials: ";

	int trials;
	cin >> trials;

	int* outcomes = new int[n_dice * sides + 1];

	for (int j = 0; j < trials; ++j)
		outcomes[(d1 = r_sides()) + (d2 = r_sides())]++;

	cout << "Probability\n";

	for (int j = 2; j < n_dice * sides; ++j) // the scope of variable 'j' is local to the for loop here.
		cout << "j = " << j << "p = "
			 << static_cast<double>(outcomes[j])/trials
			 << endl;

	return (0);
}
