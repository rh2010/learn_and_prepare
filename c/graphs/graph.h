#include "../util.h"

/*
 * Adjacency list to represent graphs.
 *
 * - adjancency list are better for most problems.
 * - they are faster in traversing the graph: O(m+n) vs O(n2) for adjacency matrix
 * - faster to find the degree of a node
 * - It takes less memory on sparse (small) graphs.
 *
 * Adjacency Matrix:
 * - Faster to test if (x, y) is in graph
 * - Less memory on bug graphs.
 * - Egde insertion and deletion is O(1).
 */
#ifndef _GRAPH_H_
#define _GRAPH_H_

#define MAXV	1000	// maximum number of vertices.

typedef struct edgenode {
	int y; // adjacency infomation
	int weight;
	struct edgenode *next;
} edgenode_t;

typedef struct graph {
	int nvertices;
	int nedges;
	bool directed;
	int degree[MAXV+1];
	edgenode_t *edges[MAXV+1];
} graph_t;

// init a graph
//
void graph_init(graph_t *graph);
// add a new vertice to the graph
//
graph_t *graph_add_vertice(graph_t *graph, int vertice);
// add a new edge to the graph
//
graph_t *graph_add_edge(graph_t *graph, int from_vertice, int to_vertice);
// print the graph
//
void graph_print(graph_t *graph);
// Traverse the graph in BFS way
//
void graph_traverse_bfs(graph_t *graph);
// Traverse the graph in DFS way
//
void graph_traverse_bfs(graph_t *graph);
//
#endif // _GRAPH_H_

