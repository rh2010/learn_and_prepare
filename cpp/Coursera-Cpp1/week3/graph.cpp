#include <iostream>
#include <cstdbool>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

const char *graph_file;

// Class for representing a graph using adjacency list.
class graph {

	// init params for the graph
	int max_vertices; // The number of vertices to which the graph should goto.
	int vertices_count; // the current vertex count in the graph 

	unsigned int edge_density; // Edge density: ranges between 1 - 10.
							   // 1 -> 10 percent
							   // 2 -> 20 percent
							   // 3 -> 30 percent
							   // ...
							   // 10 -> 100 percent i.e. A Complete Graph
	unsigned int weight_range;
	bool directed; // used when inserting edge.

	struct vertice;
	//int nedges; // not really needed

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
		char node; // either use val or node
		//int degree;
		int edge_count;
		bool is_visited;
		struct vertice *next;

		// edges can also be a hash-map for faster lookups.
		struct edge *edges;
	} *vertices;

	// TODO: vertices should ideally be a hash-map
	// so, looking up a vertice is quick.
	//

	int
	get_max_vertex_count(void)
	{
		// return a random number from 50 - 52.
		// for now keep it fixed at 50.
		return (max_vertices);
	}

	unsigned int
	get_edge_density(void)
	{
		return edge_density;
	}

	unsigned int
	get_weight(void)
	{
		// return a random value between 1 - 11.
		return ((rand() % weight_range) + 1);
	}

	char
	get_new_vertex_value(void)
	{
		// TODO: Randomly return a character between a-z or A-Z.
		int rand_val = rand() % get_max_vertex_count();
		char val;

		if (rand_val < 26) {
			// 0 - 25
			// A - Z
			val = static_cast<char>('A' + rand_val);
		} else {
			// 26 - 51
			// a  - z
			val = static_cast<char>('a' + (rand_val - 26));
		}
		//cout << "get_new_vertex_value: " << rand_val << "-> " << val << endl;

		return val;
	}

	char
	get_second_vertex_for_edge(char s)
	{
		char t;

		do {
			t = get_new_vertex_value();
		} while (t == s);

		return t;
	}

	char
	get_vertex_value(vertice *v)
	{
		assert(v != NULL);

		return v->node;
	}

	vertice*
	get_new_vertice(char value)
	{
		vertice *v = new vertice;
		if (v == NULL) {
			printf("Error: Unable to get memory for vertice\n");
			return NULL;
		}

		// initialize everything with zero.
		//memset(v, 0, sizeof(*v));

		// set the value of the vertice.
		v->node = value;
		v->edge_count = 0;
		v->next = NULL;
		v->edges = NULL;
		v->is_visited = false;
		printf("get_new_vertice: Created vertex [%p], value [%c]\n", v, v->node);

		return v;
	}

	// the vertice will be the to vertice.
	edge*
	get_new_edge(vertice* vertice, int weight)
	{
		edge *e = new edge;
		if (e == NULL) {
			printf("Error: Unable to allocate memory for edge\n");
			return NULL;
		}

		e->vertice = vertice;
		e->weight = weight;
		e->next = NULL;

		return e;
	}

	vertice*
	find_vertice(char  value)
	{
		vertice *temp = vertices;

		if (vertices == NULL) {
			return NULL;	
		}

		if (vertices_count == 0) {
			return NULL;	
		}

		while (temp != NULL) {
			if (temp->node == value) {
				//printf("Found vertice %d : %p\n", value, temp);
				return temp;
			}
			temp = temp->next;
		}
		assert(temp == NULL);

		//printf("%c not in the existing vertices.\n", value);

		return NULL;
	}

	void
	create_graph_randomly(void);

	void
	build_graph_from_file(void)
	{
		cout << "Empty" << endl;
	}

	public:
		// constructor
		graph(bool is_directed)
		{
			directed = is_directed;
			vertices_count = 0;
			max_vertices = 0;
			directed = false;
			vertices = NULL;

			// All manually done.	
		}

		// constructor
		graph(char *graph_file)
		{
			vertices_count = 0;
			max_vertices = 0;
			directed = false;
			vertices = NULL;

			/*
			 * Edge density and weight_range doesn't matter.
			 * Everything will get populated from the file.
			 */
			
			// set the seed for rand()
			// though not needed if we are reading the graph from a file.
			srand(clock());

			// Build the graph from the file.
			build_graph_from_file();
		}
		
		// constructor
		graph(bool is_directed,
			  int num_vertices,
			  unsigned int density,
			  unsigned int range_distance)
		{
			vertices_count = 0;
			max_vertices = num_vertices;
			directed = is_directed;
			vertices = NULL;
			edge_density = density;
			weight_range = range_distance;

			// set the seed for rand()
			srand(clock());

			// Create the graph randomly from input parameters.
			cout << "Creating graph with params" << endl;
			cout << "is_directed: " << directed << endl;
			cout << "Maximum vertices: " << max_vertices << endl;
			cout << "Edge density: " << edge_density << endl;
			cout << "Weight Range: " << weight_range << endl << endl;
			
			create_graph_randomly();
		}

		// default constructor
		graph()
		{
			vertices_count = 0;
			max_vertices = 0;
			directed = false;
			vertices = NULL;
			edge_density = 2; // default edge density : 20%
			weight_range = 10; // default range is 1 - 10

			// set the seed for rand()
			srand(clock());
		}
	
		vertice* add_vertice(char data);

		bool
		add_edge(char from, char to)
		{
			return add_edge(from, to, 0);
		}

		bool
		add_edge(char from, char to, int weight)
		{
			vertice *from_vertice;
			vertice *to_vertice;
			vertice *temp_vertice;
			edge *new_edge;
			edge *temp;
			unsigned int add_new_edge = (directed ? 1 : 2);

			from_vertice = find_vertice(from);
			if (from_vertice == NULL) {
				printf("From vertice %c present, adding it ...\n", from);

				from_vertice = add_vertice(from);
				if (from_vertice == NULL) {
					printf("Error: Unable to add a new_vertice %c \n", from);
					return false;
				}
			}

			to_vertice = find_vertice(to);
			if (to_vertice == NULL) {
				printf("To vertice %c not present, adding it ... \n", to);

				to_vertice = add_vertice(to);
				if (to_vertice == NULL) {
					printf("Error: Unable to add a new_vertice %c \n", to);
					return false;
				}
			}


			while (add_new_edge > 0) {
				//printf("Adding edge: %c -> %c : %d (w)).\n",
				//		from_vertice->node, to_vertice->node, weight);
			
				// No loops in the graph.
				assert(to_vertice != from_vertice);

				// get the new edge.
				new_edge = get_new_edge(to_vertice, weight);
				if (new_edge == NULL) {
					printf("Error: Unable to get a new edge(%c -> %c : %d (w))\n",
							from, to, weight);
					return false;
				}

				// No loops in the graph.
				assert(new_edge->vertice != from_vertice);

				temp = from_vertice->edges;

				// first edge
				if (from_vertice->edges == NULL) {
					from_vertice->edges = new_edge;
					goto next;
				}

				// get to the last edge.
				while(temp->next != NULL) {
					if (temp->vertice == to_vertice) {
						printf("Edge %c -> %c already present : %d (w)\n",
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
				//printf("Edge: %c -> %c : %d (w)) added.\n",
				//		from_vertice->node, to_vertice->node, weight);
				add_new_edge--;

				// swap to and from pointers to add the reverse edge incase of un-directed graph.
				temp_vertice = from_vertice;
				from_vertice = to_vertice;
				to_vertice = temp_vertice;
			}

			return true;
		}

		bool
		edge_present_in_vertice(vertice *v, char edge_val)
		{
			edge *e;

			assert(v);

			if (v->edge_count == 0) {
				return false;
			}

			e = v->edges;

			while(e != NULL) {
				if (e->vertice->node == edge_val) {
					printf("edge_present_in_vertice: %c -> %c\n", v->node, edge_val);
					return  true;
				}
				e = e->next;
			}
			return false;
		}

		// print the graph
		void
		show()
		{
			vertice *tempv;
			edge *tempe;

			printf("Graph:\n");
			printf("\tVertices count: %d\n", vertices_count);
			printf("\t%s\n", directed ? "Directed" : "Un-directed");
			printf("\tMax Vertices count: %u\n", max_vertices);
			printf("\tEdge density: %u\n", edge_density);
			printf("\tWeight range: %u\n", weight_range);

			printf("Vertices and Edges:\n");

			tempv = vertices;
			while (tempv != NULL) {
				tempe = tempv->edges;

				printf("[%c]: ", tempv->node);
				while (tempe != NULL) {
					printf("--{%d}-> (%c) ", tempe->weight, tempe->vertice->node);
					// next edge
					tempe = tempe->next;
				}
				printf("\n");

				// next vertice
				tempv = tempv->next;
			}
		}

		void
		dijkistra(int from, int to)
		{
			printf("Empty\n");
		}
};

/*
 * Add a vertice in the graph.
 */
graph::vertice*
graph::add_vertice(char data)
{
	vertice *temp;
	vertice *head = vertices;

	cout << "add_vertice [" << data << "] " << endl;

	if (find_vertice(data)) {
		printf("Error: vertice %c already present\n", data);
		return NULL;
	}

	vertice *new_vertice = get_new_vertice(data);
	if (new_vertice == NULL) {
		printf("Error: Failed to get a new vertice\n");
		exit(-1);
	}

	// first vertice.
	if (head == NULL) {
		vertices = new_vertice;
		goto done;
	}

	// goto the last vertice and add after that.
	temp = head;
	while(temp->next != NULL) {
		temp = temp->next;
	}

	// add the new_vertice in the list
	temp->next = new_vertice;

	// done
done:
	vertices_count++;
	//printf("Added vertex [%c]\n", new_vertice->node);
	cout << "[" << vertices_count <<"] Added vertex [" << data << "] " << endl;
	return new_vertice;
}

/*
 * create the graph : randomly
 */
void
graph::create_graph_randomly(void)
{
	char v;
	char t; // target vertex for a new edge.
	vertice *vertex;
	int edges;
	int w;

	cout << "Entry : create_graph_randomly" << endl << endl;

	while (vertices_count != max_vertices) {
	
		// get a new vertex to add to the graph
		v = get_new_vertex_value();
		printf("[%d: %d] New Vertex: %c\n\n", vertices_count, max_vertices, v);

		vertex = find_vertice(v);
		if (vertex == NULL) {
			// add the vertex to the graph
			cout << "Adding vertex: " << v << endl;
			vertex = add_vertice(v);
			assert(vertex != NULL);
		}
		edges = (edge_density * max_vertices)/ 10;

		if (edges <= vertex->edge_count) {
			cout << "Vertex " << v << "  is already processed " << edges << ": Max : " << vertex->edge_count << endl;
			// vertex already processed 
			continue;
		}

		cout << "Adding edges to vertex " << v << endl;

		// Add edges to the vertex.
		while (vertex->edge_count < edges) {

			// get a new vertex to add an edge too.
			t = get_second_vertex_for_edge(v);
			printf("[%d: %d] %c -> %c \n", vertex->edge_count, edges, v, t);

			// if the edge is not already present, add the edge
			if (edge_present_in_vertice(vertex, t)) {
				continue;
			}

			// get a weight to attach to the edge
			w = get_weight();

			printf("adding edge %c -> %c [%u]\n", v, t, w);
			// add the edge
			add_edge(v, t, w);
		}
	}
	cout << "Exit : create_graph_randomly" << endl;
}

void
show_menu()
{
	printf("1. Add vertice\n");
	printf("2. Add Edge\n");
	printf("3. Display graph\n");
	printf("4. Shortest path\n");
	printf("0. Exit\n");
	printf("Enter choice: ");
}

int
main(int argc, char **argv)
{
	bool is_directed = false;
	int num_vertices;
	unsigned int e_density;
	unsigned int w_range;
	bool done = false;
	char value;
	char to, from;
	int w;

	if (argc == 1) {
		cout << "usage: ./a.out <number of vertices> "
				"<edge density> <range of edge weights>" << endl;
		exit(-1);
	}

	// initialze the graph
	
	if (argc == 4) {
		// count of vertices in the graph
		num_vertices = atoi(argv[1]);

		// density of edges
		e_density = atoi(argv[2]);

		// range of weights
		w_range = atoi(argv[3]);

	} else {
		cout << "usage: ./a.out <number of vertices> "
				"<edge density> <range of edge weights>" << endl;
		exit(-1);

	}
	/*
	if (argc == 2) {
		is_directed = true;
		graph_file = argv[1]; // just for degubbing
		printf("Initializing the graph from file: %s\n", graph_file);
		graph g(argv[1]);

	} else if (argc == 4) {
		// count of vertices in the graph
		num_vertices = atoi(argv[1]);

		// density of edges
		e_density = atoi(argv[2]);

		// range of weights
		w_range = atoi(argv[3]);

		graph g(is_directed, num_vertices, e_density, w_range);
	} else {
		printf("Initializing an Un-Directed graph\n");
		graph g(is_directed);
	}*/

	graph g(is_directed, num_vertices, e_density, w_range);

	int choice;

	while(!done) {

		show_menu();

		cin >> choice;

		switch (choice) {
			case 1:
				printf("Vertice to add: ");
				cin >> value;
				g.add_vertice(value);
				break;

			case 2:
				printf("Edge to add (from, to): ");
				cin >> from >> to >> w;
				g.add_edge(from, to, w);
				break;

			case 3:
				g.show();
				break;

			case 4:
				printf("Shortest path between (from, to): ");
				cin >> from >> to;
				g.dijkistra(from, to);
				break;

			case 0:
				done = true;
				printf("Exiting ...\n");
				break;
			default:
				printf("Unknown option, try again\n");
				break;
		}
	}

	return (0);
}
