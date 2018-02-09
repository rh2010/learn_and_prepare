#include <iostream>
#include <cstdbool>
#include <cassert>
#include <cstring>

using namespace std;

// Class for representing a graph using adjacency list.
class graph {
	int vertices_count;
	//int nedges; // not really needed
	bool directed; // used when inserting edge.

	// An edge in the graph.
	struct edge {
		int weight; // an edge might or might not have a weight associated with it.

		// pointer to the next edge from the same vertice.
		struct edge *next;

		// pointer to the other vertice which this edge consists of.
		struct vertice *vertice;
	};

	// A vertice in the graph.
	struct vertice {
		int val;
		//char node; // either use val or node
		int degree;
		int edge_count;
		bool isVisited;
		struct vertice *next;

		// edges can also be a hash-map for faster lookups.
		struct edge *edges;
	} *vertices;

	// vertices should ideally be a hash-map
	// so, looking up a vertice is quick.
	//

	struct vertice*
	get_new_vertice(int vertice)
	{
		struct vertice *v = (struct vertice*)new(sizeof (struct vertice));
		if (v == NULL) {
			printf("Error: Unable to get memory for vertice\n");
			return NULL;
		}

		// initialize everything with zero.
		memset(v, 0, sizeof(*v));

		// set the value of the vertice.
		v->val = vertice;
		return v;
	}

	// the vertice will be the to vertice.
	struct edge*
	get_new_edge(struct vertice* vertice, int weight)
	{
		struct edge *e = (struct edge*)new(sizeof(struct edge));
		if (e == NULL) {
			printf("Error: Unable to allocate memory for edge\n");
			return NULL;
		}

		e->vertice = vertice;
		e->weight = weight;
		e->next = NULL;

		return e;
	}

	struct vertice*
	find_vertice(int vertice)
	{
		struct vertice* temp;
		temp = vertices;

		if (vertices == NULL) {
			return NULL;	
		}

		if (vertices_count == 0) {
			return NULL;	
		}

		while (temp != NULL) {
			if (temp->val == vertice) {
				return temp;
			}
			temp = temp->next;
		}
		assert(temp != NULL);

		printf("%d not in the existing vertices.\n", vertice);

		return NULL;
	}

	public:
		// constructor
		graph(bool isDirected)
		{
			vertices = 0;
			directed = isDirected;
			vertices = NULL;
		}
		
		// default constructor
		graph()
		{
			vertices = 0;
			directed = false;
			vertices = NULL;
		}
		
		void
		add_vertice(int data)
		{
			struct vertice *temp;
			struct vertice *new_vertice = get_new_vertice(data);
			struct vertice *head = vertices;

			if (new_vertice == NULL) {
				printf("Error: Failed to get a new vertice\n");
				exit(-1);
			}

			// first vertice.
			if (head == NULL) {
				vertices = new_vertice;
				return;
			}

			// goto the last vertice and add after that.
			temp = head;
			while(temp->next != NULL) {
				temp = temp->next;
			}

			// add the new_vertice in the list
			temp->next = new_vertice;

			// done
			return;
		}

		bool
		add_edge(int from, int to, int weight)
		{
			struct vertice *from_vertice;
			struct vertice *to_vertice;
			struct edge *new_edge;
			struct edge *temp;
			unsigned int add_edge = (directed ? 1 : 2);

			from_vertice = find_vertice(from);
			if (from_vertice == NULL) {
				printf("Error: vertice %d not found \n", from);
				return false;
			}

			to_vertice = find_vertice(to);
			if (to_vertice == NULL) {
				printf("Error: vertice %d not found \n", to);
				return false;
			}

			new_edge = get_new_edge(to_vertice, weight);
			if (new_edge) {
				printf("Error: Unable to get a new edge(%d -> %d : %d(w))\n",
						from, to, weight);
				return false;
			}

			while (add_edge > 0) {
				temp = from->edges;

				// first edge
				if (from_vertice->edges == NULL) {
					from_vertice->edges = new_edge;
					goto next;
				}

				// get to the last edge.
				while(temp->next != NULL) {
					if (temp->vertice == to_vertice) {
						printf("Edge %d -> %d already present : %d(w)\n",
								from, to, temp->weight);

						// free up the new edge.
						delete(new_edge);
						return false;
					}
					temp = temp->next;
				}

				// add the new edge to the list
				temp->next = new_edge;

			next:
				from_vertice->edge_count++;
				printf("Edge: %d -> %d : %d (w)) added.\n", from, to, weight);
				add_edge--;

				// swap to and from pointers to add the reverse edge incase of un-directed graph.
				temp = from_vertice;
				from_vertice = to_vertice;
				to_vertice = temp;
			}

			// print the graph
			void
			show()
			{
				struct vertice *tempv;
				struct edge *tempe;

				printf("Graph:\n");
				printf("\tVertices count: %d\n", vertices_count);
				printf("\t%s\n", directed ? "Directed" : "Un-directed");

				printf("Vertices and Edges:\n");

				tempv = vertices;
				while (tempv != NULL) {
					tempe = tempv->edges;

					printf("[%d]: ", tempv->val);
					while (tempe != NULL) {
						printf("-> (%d) ", tempe->vertice->val);
						// next edge
						tempe = tempe->next;
					}

					// next vertice
					tempv = tempv->next;
				}
			}

			void
			dijkistra(int from, int to)
			{
				printf("Empty\n");
			}
			return true;
		}
};

