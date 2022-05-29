#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdbool>

using namespace std;

bool isSubstr(string s, string t) {
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < t.size(); j++) {
			if (s[i+j] != t[j]) {
				break;
			}
			if (j == t.size()-1) {
				return true;
			}
		}
	}
	return false;
}

int main(int argc, char **argv)
{
	string s1("abcddafassdd");
	string s2("cdda");
	string s3("cdas");
	string s4("daf");

	printf("%s is substring of %s (%d)\n", s2.c_str(), s1.c_str(), isSubstr(s1, s2));
	printf("%s is substring of %s (%d)\n", s3.c_str(), s1.c_str(), isSubstr(s1, s3));
	printf("%s is substring of %s (%d)\n", s4.c_str(), s1.c_str(), isSubstr(s1, s4));

	return (0);
}
