# 
# Makefile for:
# 	test.cpp
# 	test2.cpp
# 	mst.cpp : Minimum spanning tree.
#

.PHONY : all test mst test2 clean

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

clean:
	rm -f a.out
	rm -f mst
	rm -f test2
	rm -f test
