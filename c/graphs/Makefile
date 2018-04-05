.PHONY: all clean graph

all: clean
	gcc -o graph graph.c queue.c test_graph.c

graph:
	rm -f graph
	gcc -o graph graph.c queue.c test_graph.c

clean:
	rm -f graph
