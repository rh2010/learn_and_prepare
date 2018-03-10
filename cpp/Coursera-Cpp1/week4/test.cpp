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

	char ch = 'b';

	ch += 2;
	cout << ch << endl;

	int a =2, b = -3, c = 2;

	cout << "b + c * a = " << (b + c * a) << endl;
	cout << "c % 5 /2 = " << (c % 5 / 2) << endl;
	cout << "-a *c++  = " << (-a * c++) << endl;

	vector<int> data(5, 1);
	int sum{0};

	cout << sum << endl;

	for (auto element : data) {
		cout << "adding " << element << endl;
		sum += element;
	}

	cout << sum << endl;

	for(auto p = ++data.begin(); p != --data.end(); ++p) {
		cout << "adding " << *p << endl;
		sum += *p;
	}

	cout << sum << endl;

	sum = 0;

	cout << "sum ... re-inited\n";
	data.push_back(2);

	data.push_back(3);

	for(auto element : data) {
		cout << "adding " << element << endl;
		sum += element;
	}

	cout << sum << endl;

	cout << accumulate(data.begin(), data.end(), data[0]) << endl;

}

