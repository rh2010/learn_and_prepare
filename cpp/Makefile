.PHONY: all clean jobs

all: clean
	g++ -std=c++11 -o jobs jobs.cpp

jobs:
	rm -f jobs
	g++ -std=c++11 -o jobs jobs.cpp
	./jobs jobs.test

clean:
	rm -f a.out
	rm -f jobs
