#include <cstdio>
#include <unordered_map>
#include <cstring>
#include <cstdlib>

using namespace std;

class Trie {

	class TrieNode {
		bool end;
		unordered_map<char, TrieNode*> children;

		public:

		// Ctor
		TrieNode():
		end(false) {
		}

		void setWord() {
			this->end = true;
		}

		bool isWord() {
			return this->end;
		}

		TrieNode *addChild(char c) {
			if (children.find(c) == children.end()) {
				children.insert(make_pair(c, new TrieNode()));
			}

			return children[c];
		}

		TrieNode *getChild(char c) {
			if (children.find(c) != children.end()) {
				return children[c];
			}
			return nullptr;
		}

	};

	// root of the Trie
	TrieNode *root;

	public:
	Trie() {
		this->root = new TrieNode();
	}

	void insert(string word) {
		TrieNode *curr = this->root;

		for (auto c : word) {
			curr = curr->addChild(c);
		}
		curr->setWord();
	}

	bool search(string word) {
		TrieNode* curr = this->root;

		for (auto c : word) {
			curr = curr->getChild(c);
			if (curr == NULL) {
				return false;
			}
		}
		return curr->isWord();
	}
};

int main(int argc, char **argv) {

	if (argc < 2) {
		printf("Error: Bad input\n");
		printf("\t./trie: <list-of-strings to add> <string-to-find>.\n");
		exit(-1);
	}

	Trie t;

	int i= 1;

	// build the trie
	while (i < argc-1) {
		printf("Adding %s to trie.\n", argv[i]);
		t.insert(argv[i]);
		i++;
	}

	// find
	printf("Is (%s) in the trie [%s]\n.", argv[argc-1], (t.search(argv[argc-1])?"Yes":"No"));

	return (0);
}
