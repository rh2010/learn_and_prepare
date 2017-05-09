#include "graph.h"

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
			new = NULL;
			goto error;
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
		goto out;
		/*
		from = graph_add_vertice(g, from_vertice);
		if (from == NULL) {
			printf("Unable to add a new vertice %d\n", from_vertice);
			goto out;
		}
		printf("Added new vertice %d\n", from_vertice);
		*/
	}

	if (to == NULL) {
		printf("Vertice: %d if not present in graph!", to_vertice);
		goto out;
		/*
		to = graph_add_vertice(g, to_vertice);
		if (to == NULL) {
			printf("Unable to add a new vertice %d\n", to_vertice);
			goto out;
		}
		printf("Added new vertice %d\n", to_vertice);
		*/
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
	if (!g->directed) {
		// if graph is not directed then add the reverse edge too.
		if (graph_add_edge(g, to_vertice, from_vertice, weight)) {
			// if an edge was actually added (which would be the reverse edge
			// the adjust the double increment of nedges.
			g->nedges--;
		}
	}
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
	v = find_vertice(g, start);
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
	v = find_vertice(g, start);
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

// given a value find it's corresponding vertice node.
vertice_t *
find_vertice(graph_t *g, int val)
{
	vertice_t *v;
	v = NULL;

	assert(g != NULL);

	v = g->vertices;

	if (v == NULL) {
		printf("Empty graph, no vertex with val %d\n", val);
		assert(g->nvertices == 0);
		goto out;
	}

	while (v != NULL) {
		if (v->val == val) {
			break;
		}
		v = v->next;
	}

	if (v == NULL) {
		printf("Starting vertice %d, Not Found!\n", val);
	}

out:
	return v;
}

bool
graph_hasCycles(graph_t *g)
{
	assert(g != NULL);
	assert(g->directed);

	return FALSE;
}

/*
 * DFS used for topological sort.
 * Takes pointer to the graph and pointer to the starting
 * vertex to perform DFS.
 */
void
graph_dfs(graph_t *g, vertice_t *starting_vertex, stack_head_t *res)
{
	vertice_t *t; // temp
	vertice_t *v; // temp
	stack_head_t stack;
	stack_head_t *s;
	edge_t *e;
	int count;

	assert(g != NULL);
	assert(starting_vertex != NULL);
	assert(s != NULL);

	// we shouldn't start a DFS from a already visited vertex.
	assert(!starting_vertex->isVisited);

	s = &stack;
	stack_init(s);

	t = starting_vertex;
	// we have 'v' as the starting vertice
	//
	push(s, t);
	t->isVisited = TRUE;

	while (!stack_is_empty(s)) {
		t = pop(s);

		// pre-process node v.
		//printf("%d ", v->val);
		e = t->edges;
		count = 0;

		while (e != NULL) {
			v = e->vertice; // get the 2nd vertice of edge

			if (!v->isVisited) {
				v->isVisited = TRUE;
				if (count == 0) {
					/*
					 * push the vertex whose edges we are processing back on
					 * the stack if it has at least one edge which is not yet
					 * processed.
					 *
					 * We push the vertex being processed back on the stack
					 * so that when it has no out-going edges left to process
					 * it can go on the result stack.
					 *
					 * Essentially, this implements Kahn's Alrogithm.
					 */
					push(s, t);
				}
				push(s, v);
				count++;
			}
			e = e->next;
		}
		/*
		 * We will only push a vertex onto the result stack when it
		 * has no out going edges left to process.
		 *
		 * A count of '0' represent that no edges were processed in this loop.
		 */
		if (count == 0) {
			// push the vertex 't' on the result stack
			push(res, t);
		}
	}

	stack_uninit(s);
	return;
}

void
graph_topologicalSort(graph_t *g)
{
	stack_head_t result;
	stack_head_t *r;
	vertice_t *v;
	edge_t *e;

	assert(g != NULL);

	v = g->vertices;

	if (!g->directed) {
		printf("graph_topologicalSort: Can't run topological sort on undirected"
				" graph\n");
		printf("graph_topologicalSort: Topological Sort can only be run on a "
				" Directed Acyclic Graph (DAG)\n");
		return;
	}

	if (v == NULL) {
		printf("graph_topologicalSort: Empty Graph\n");
		return;
	}

	if (graph_hasCycles(g)) {
		printf("graph_topologicalSort: Graph has cycles\n");
		printf("graph_topologicalSort: Topological Sort can only be run on a "
				" Directed Acyclic Graph (DAG)\n");
		return;
	}
	r = &result;

	// stack to hold the topologoical sorting order
	stack_init(r);

	// For each vertex, if it is not already visited, do a DFS.
	while (v != NULL) {
		if (!v->isVisited) {
			graph_dfs(g, v, r);
		}
		v = v->next;
	}

	// print the result stack
	printf("Topological Sort Order is:\n");
	while(!stack_is_empty(r)) {
		v = (vertice_t *)pop(r);
		printf("%d ", v->val);
	}
	printf("\n");

	stack_uninit(r);

	return;
}
