#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cstdlib>

//
// Read a series of words into a vertor and sort them.
//
using namespace std;

const char file_name[] = "mst_test.data";

int
main(int argc, char **argv)
{
	int num_vertices;
	int x, y, w;

	// open the file to be read
	ifstream word_file(file_name);

	// get the num vertices.
	word_file >> num_vertices;

	cout << num_vertices << endl;

	// get edge pairs along with weight.
	while (word_file >> x >> y >> w) {
		cout << x << " -> " << y << " : " << w << endl;
	}

	cout << endl;
}

