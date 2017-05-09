#include "graph.h"
#include "queue.h"

/*
 * Implement:
 * 	- Graph creation (a.k.a. graph addition)
 * 	- Deletion from a graph
 * 	- Search a graph
 * 		- DFS
 * 		- BFS
 *
 */

/*
 * Read a graph from a file and build a graph.
 */

// init a graph
//
void
graph_init(graph_t *g, bool directed)
{
	assert(g!= NULL);

	g->nvertices = 0;
	g->nedges = 0;
	g->vertices = NULL;
	g->directed = directed;

	return;
}

vertice_t *
get_new_vertice(int vertice)
{
	vertice_t *new;

	new = (vertice_t *)malloc(sizeof (vertice_t));
	if (new == NULL) {
		printf("get_new_vertice: No Memory!\n");
		return NULL;
	}
	new->val = vertice;
	new->node = '.'; // the default value of node
	new->degree = 0;
	new->edge_count = 0; // no edges initially
	new->isVisited = FALSE;
	new->next = NULL;
	new->edges = NULL; // no edges initially

	return new;
}

// add a new vertice to the graph
//
vertice_t *
graph_add_vertice(graph_t *g, int vertice)
{
	vertice_t *temp, *new, *prev;

	assert(g!= NULL);

	temp = g->vertices;
	prev = NULL;
	new = NULL;

	new = get_new_vertice(vertice);
	assert(new);
	if (new == NULL) {
		printf("Unable to get new vertice\n");
		goto error;
	}

	if (temp == NULL) {
		// first vertice
		g->vertices = new;
		goto out;
	}

	while (temp != NULL) {
		prev = temp;
		if (temp->val == vertice) {
			printf("Vertice %d already present\n", vertice);
			free(new);
			goto out;
		}
		temp = temp->next;
	}
	// after the loop prev points to the last vertice node.
	prev->next = new;

out:
	g->nvertices++;
error:
	return new;
}

edge_t *
get_new_edge(vertice_t *to, int weight)
{
	edge_t *new;

	assert(to != NULL);

	new = (edge_t *)malloc(sizeof (edge_t));
	if (new == NULL) {
		printf("get_new_vertice: No Memory!\n");
		return NULL;
	}
	new->weight = weight;
	new->next = NULL;
	new->vertice = to;

	return new;
}

// add a new edge to the graph
//
edge_t *
graph_add_edge(graph_t *g, int from_vertice, int to_vertice, int weight)
{
	vertice_t *from, *to, *temp;
	edge_t *new, *te, *prev;

	assert(g!= NULL);
	printf("graph_add_edge: (%d, %d) \n", from_vertice, to_vertice);

	temp = g->vertices;
	from = to = NULL;
	new = NULL;

	while (temp != NULL) {
		if (temp->val == from_vertice) {
			from = temp;
		}
		if (temp->val == to_vertice) {
			to = temp;
		}

		// if both the nodes are found, break the loop
		if ((from != NULL) && (to != NULL)) {
			break;
		}
		temp = temp->next;
	}

	if (from == NULL) {
		printf("Vertice: %d if not present in graph!", from_vertice);
		from = graph_add_vertice(g, from_vertice);
		if (from == NULL) {
			printf("Unable to add a new vertice %d\n", from_vertice);
			goto out;
		}
		printf("Added new vertice %d\n", from_vertice);
	}

	if (to == NULL) {
		printf("Vertice: %d if not present in graph!", to_vertice);
		to = graph_add_vertice(g, to_vertice);
		if (to == NULL) {
			printf("Unable to add a new vertice %d\n", to_vertice);
			goto out;
		}
		printf("Added new vertice %d\n", to_vertice);
	}

	// We have located both from and to vertices.
	te = from->edges;

	new = get_new_edge(to, weight);
	assert(new);
	if (new == NULL) {
		printf("Unable to get new vertice\n");
		goto out;
	}

	// First edge
	if (te == NULL) {
		from->edges = new;
		goto success; // Done
	}

	prev = NULL;
	while (te != NULL) {
		prev = te;
		if (te->vertice->val == to->val) {
			assert(te->vertice == to); // double checking
			printf("Edge (%d, %d) already present the in graph\n",
					from_vertice, to_vertice);
			goto error;
		}
		te = te->next;
	}
	// prev points to the last edge.
	prev->next = new;

success:
	graph_add_edge(g, to_vertice, from_vertice, weight);
	g->nedges++;
out:
	return new;

error: // All error cases post allocation of the new edge.
	free(new);
	new = NULL;
	goto out;

}

// print the graph
//
void
graph_print(graph_t *g)
{
	vertice_t *tv; // temp pointer for vertice traversal.
	edge_t *te; // temp pointer for edge traversal.

	assert(g!= NULL);

	printf("Graph:\nVertices: %d\nEdges: %d\n", g->nvertices, g->nedges);
	tv = g->vertices;

	while (tv != NULL) {
		printf("%d := ", tv->val);
		te = tv->edges;

		while (te != NULL) {
			printf("%d -> ", te->vertice->val);
			te = te->next;
		}
		printf("\n");
		tv = tv->next;
	}

	return;
}

void
graph_uninit(graph_t *g)
{
	vertice_t *tv, *pv;
	edge_t *te, *pe;

	assert(g!= NULL);

	tv = g->vertices;
	pv = NULL;

	while (tv != NULL) {
		te = tv->edges;
		pe = NULL;

		while (te != NULL) {
			pe = te;
			te = te->next;
			free(pe);
		}
		pv = tv;
		tv = tv->next;
		free(pv);
	}

	g->vertices = NULL;
	g->nvertices = 0;
	g->nedges = 0;

	return;
}

// Traverse the graph in BFS way
//
void
graph_traverse_bfs(graph_t *g, int start)
{
	queue_head_t q;
	vertice_t *v;
	edge_t *e;

	assert(g!= NULL);

	queue_init(&q);

	// find the starting vertice
	//
	v = g->vertices;
	if (v == NULL) {
		printf("Empty Graph, no vertices\n");
		return;
	}

	while (v != NULL) {
		if (v->val == start) {
			break;
		}
		v = v->next;
	}

	if (v == NULL) {
		printf("Starting vertice %d, Not Found!\n", start);
		return;
	}

	// v is the starting vertice.
	//
	enqueue(&q, v);
	v->isVisited = TRUE;

	while (!queue_is_empty(&q)) {
		v = dequeue(&q);

		// pre-process node v
		printf("%d ", v->val);
		e = v->edges;

		while (e != NULL) {
			v = e->vertice;
			if (!v->isVisited) {
				v->isVisited = TRUE;
				enqueue(&q, v);
			}
			e = e->next;
		}
		// post-process vertice 'v'
	}
	return;
}

// Traverse the graph in DFS way
//
void
graph_traverse_dfs(graph_t *g, int start)
{
	stack_head_t s;
	vertice_t *v;
	edge_t *e;

	assert(g!= NULL);

	stack_init(&s);

	// Find the starting vertex
	v = g->vertices;
	if (v == NULL) {
		printf("Empty Graph, no vertices\n");
		return;
	}

	while (v != NULL) {
		if (v->val == start) {
			break;
		}
		v = v->next;
	}
	if (v == NULL) {
		printf("Starting vertice %d, Not Found!\n", start);
		return;
	}

	// we have 'v' as the starting vertice
	//
	push(&s, v);
	v->isVisited = TRUE;

	while (!stack_is_empty(&s)) {
		v = pop(&s);

		// pre-process node v.
		printf("%d ", v->val);
		e = v->edges;

		while (e != NULL) {
			v = e->vertice; // get the 2nd vertice of edge

			if (!v->isVisited) {
				v->isVisited = TRUE;
				push(&s, v);
			}
			e = e->next;
		}
		// post process vertice 'v'
	}

	return;
}

// After a traverse - mark all vertices as not visited.
//
void
graph_clear_visited(graph_t *g)
{
	vertice_t *temp;

	assert(g != NULL);
	temp = g->vertices;

	while(temp != NULL) {
		temp->isVisited = FALSE;
		temp = temp->next;
	}

	return;
}
