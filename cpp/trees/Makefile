.PHONY: all clean bst is_bst

all: clean
	g++ -std=c++11 -o bst bst.cpp

bst:
	g++ -std=c++11 -o bst bst.cpp

bst2: clean_bst2
	g++ -std=c++11 -o bst2 bst2.cpp
	./bst2

is_bst:
	g++ -std=c++11 -o is_bst is_bst.cpp

clean_bst2:
	rm -f bst2

clean:
	rm -f a.out
	rm -f bst
	rm -f bst2
	rm -f is_bst
