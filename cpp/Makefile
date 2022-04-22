.PHONY: all clean jobs

all: clean
	g++ -std=c++11 -o jobs jobs.cpp

jobs:
	rm -f jobs
	g++ -std=c++11 -o jobs jobs.cpp
	./jobs jobs.test

test:
	rm -f test
	g++ -std=c++11 -o test test.cpp

test2:
	rm -f test2
	g++ -std=c++11 -o test2 test2.cpp

uuid_test:
	rm -f uuid_test
	g++ -std=c++11 -o uuid_test uuid_test.cpp

clean:
	rm -f uuid_test
	rm -f a.out
	rm -f jobs
	rm -f test
	rm -f test2
