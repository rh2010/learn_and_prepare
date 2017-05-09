#include "../util.h"
#include "queue.h"

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

//typedef struct edgenode {
//	int val; // adjacency infomation
//	int weight;
//	struct edgenode *next;
//} edgenode_t;
//
//typedef struct graph {
//	int nvertices;
//	int nedges;
//	bool directed;
//	int degree[MAXV+1];
//	edgenode_t *edges[MAXV+1];
//} graph_t;

/*
 * NOTE: To make various operations faster we should be using a hash table in
 * conjunction with singly / doubly linked lists.
 */
typedef struct edge {
	int weight;
	// pointer to the next edge from the same vertice.
	struct edge *next;

	// pointer to the other vertice which this edge consists of.
	struct vertice *vertice;
} edge_t;

typedef struct vertice {
	int val; // or else we can use a void *data, to represent an arbitrary data.
	char node; // use either 'val' or 'char'
	int degree;
	int edge_count;
	bool isVisited;

	// singly linked to other vertices.
	struct vertice *next;

	// singly linked list for edges going out from this vertice.
	struct edge *edges;
} vertice_t;

typedef struct graph {
	int nvertices;
	int nedges;
	bool directed;

	// head pointer for the list of vertices.
	vertice_t *vertices;
} graph_t;


// init a graph
//
void graph_init(graph_t *graph, bool directed);
// add a new vertice to the graph
//
vertice_t *graph_add_vertice(graph_t *graph, int vertice);
// add a new edge to the graph
//
edge_t *graph_add_edge(graph_t *graph, int from_vertice, int to_vertice, int weight);
// print the graph
//
void graph_print(graph_t *graph);
// Traverse the graph in BFS way
//
void graph_traverse_bfs(graph_t *graph, int start);
// Traverse the graph in DFS way
//
void graph_traverse_dfs(graph_t *graph, int start);
// After a traverse - mark all vertices as not visited.
//
void graph_clear_visited(graph_t *graph);
// Create a new vertice
//
vertice_t *get_new_vertice(int vertice);
// Create a new edge
//
edge_t *get_new_edge(vertice_t *to, int weight);
// uninit a graph
//
void graph_uninit(graph_t *g);
// given a value find it's corresponding vertice node.
// 
vertice_t * find_vertice(graph_t *g, int val);
//
//
bool graph_hasCycles(graph_t *g);
//
//
void graph_dfs(graph_t *g, vertice_t *starting_vertex, stack_head_t *res);
//
//
void graph_topologicalSort(graph_t *g);
#endif // _GRAPH_H_

