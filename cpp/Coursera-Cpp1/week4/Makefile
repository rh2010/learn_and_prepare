# 
# Makefile for:
# 	test.cpp
# 	test2.cpp
# 	mst.cpp : Minimum spanning tree.
#

.PHONY : all test mst test2 clean hw

all: clean
	g++ -std=c++11 -ggdb3 -o test test.cpp
	g++ -std=c++11 -ggdb3 -o mst mst.cpp
	g++ -std=c++11 -ggdb3 -o test2 test2.cpp

test:
	g++ -std=c++11 -ggdb3 -o test test.cpp
	
mst:
	g++ -std=c++11 -ggdb3 -o mst mst.cpp

test2:
	g++ -std=c++11 -ggdb3 -o test2 test2.cpp

hw:
	g++ -std=c++11 -ggdb3 -o hw4 learning_cpp_hw4.cpp

clean:
	rm -f a.out
	rm -f mst
	rm -f test2
	rm -f test
	rm -f hw4
