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

const char file_name[] = "test.data";

int
main(int argc, char **argv)
{
	// open the file to be read
	ifstream word_file(file_name);

	// initialize 'start' as an iterator at the beginning of the file
	//
	istream_iterator<string> start(word_file), end;

	// initialize a 'vector' 'words' going from start to the end of the file.
	vector<string> words(start, end);

	cout << "Words from file are read in\n";

	// for range
	for (auto str : words) {
		cout << str << " ";
	}
	cout << endl;

	// words are sorted
	sort(words.begin(), words.end());

	for (auto str : words) {
		cout << str << " ";
	}
	cout << endl;
}

