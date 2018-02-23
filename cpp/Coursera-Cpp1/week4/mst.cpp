#include <iostream>
#include <cstdbool>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <fstream>

using namespace std;

// Class for representing a graph using adjacency list.
class graph {

	const char *graph_file;
	// init params for the graph
	const int max_vertices; // The number of vertices to which the graph should goto.
	int vertices_count; // the current vertex count in the graph 

	const unsigned int edge_density; // Edge density: ranges between 1 - 10.
							   // 1 -> 10 percent
							   // 2 -> 20 percent
							   // 3 -> 30 percent
							   // ...
							   // 10 -> 100 percent i.e. A Complete Graph
	const unsigned int weight_range;
	const bool directed; // used when inserting edge.

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
		int node; // either use val or node
		//int degree;
		int edge_count;
		bool is_visited;
		struct vertice *next;

		// edges can also be a hash-map for faster lookups.
		struct edge *edges;

		// book keeping data for shortest path.
		//
		struct sp {
			int distance;
			struct vertice *p;
		} sp;
	} *vertices;

	// TODO: vertices should ideally be a hash-map
	// so, looking up a vertice is quick.
	//

	int
	get_max_vertex_count(void)
	{
		// return a random number from 50 - 52.
		// for now keep it fixed at 50.
		assert(max_vertices <= 52);

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

	int
	get_new_vertex_value(void)
	{
		// TODO: Randomly return a character between a-z or A-Z.
		int rand_val = rand() % get_max_vertex_count();
		int val = rand_val;

		//if (rand_val < 26) {
		//	// 0 - 25
		//	// A - Z
		//	val = static_cast<char>('A' + rand_val);
		//} else {
		//	// 26 - 51
		//	// a  - z
		//	val = static_cast<char>('a' + (rand_val - 26));
		//}
		//cout << "get_new_vertex_value: " << rand_val << "-> " << val << endl;

		return val;
	}

	int
	get_vertex_value(vertice *v)
	{
		assert(v != NULL);

		return v->node;
	}

	vertice*
	get_new_vertice(int value)
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
		printf("get_new_vertice: Created vertex [%p], value [%d]\n", v, v->node);

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
	find_vertice(int value)
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

		//printf("%d not in the existing vertices.\n", value);

		return NULL;
	}

	void
	create_graph_randomly(void);

	void
	build_graph_from_file(const char *file_name)
	{
		int s, t, w;
		int num_vertices;

		cout << "build_graph_from_file : Start" << endl;
		
		assert(file_name != NULL);

		// open the file to read the i/p graph
		ifstream graph_file(file_name);

		// get the vertex count
		graph_file >> num_vertices;

		// add the edges
		while (graph_file >> s >> t >> w) {
			add_edge(s, t, w);
		}
		cout << "build_graph_from_file : End" << endl;
		assert(num_vertices == vertices_count);

		cout << "Max vertices: " << num_vertices << ", vertices added: " <<
			 vertices_count << endl;
	}

	inline bool
	vertex_visited(vertice *v)
	{
		assert(v);

		return v->is_visited;
	}

	inline void
	vertex_mark_visited(vertice *v)
	{
		assert(v);
		v->is_visited = true;
	}

	int
	vertex_distance(vertice *v)
	{
		assert(v);
		return v->sp.distance;
	}

	int
	edge_weight(edge *e)
	{
		assert(e);
		return e->weight;
	}

	void
	init_for_dijkistra(void)
	{
		vertice *temp;

		assert(vertices);
		temp = vertices;

		while (temp != NULL) {
			temp->is_visited = false;
			temp->sp.distance = INT_MAX;
			temp->sp.p = NULL;

			// next
			temp = temp->next;
		}
	}

	void
	init_for_mst(void)
	{
		init_for_dijkistra();
	}

	public:
		// constructor
		graph(bool is_directed,
			  int num_vertices,
			  unsigned int edge_density,
			  unsigned int weight_range,
			  char *graph_file)
			  :max_vertices(num_vertices),
			  directed(is_directed),
			  edge_density(edge_density),
			  weight_range(weight_range),
			  graph_file(graph_file)
		{
			vertices_count = 0;
			vertices = NULL;

			// Create the graph randomly from input parameters.
			cout << "Creating graph with params" << endl;
			cout << "is_directed: " << directed << endl;
			cout << "Maximum vertices: " << max_vertices << endl;
			cout << "Edge density: " << this->edge_density << endl;
			cout << "Weight Range: " << this->weight_range << endl << endl;
			cout << "Graph File: " << this->graph_file << endl;
		
			if (graph_file) {
				// Build the graph from the file.
				build_graph_from_file(this->graph_file);
			} else {
				create_graph_randomly();
			}
		}

		// default constructor
		graph()
		:vertices_count(0),
		max_vertices(0),
		directed(false),
		edge_density(2),  // default edge density : 20%
		weight_range(10), // default range is 1 - 10
		graph_file(NULL)
		{
			vertices = NULL;
		}

		~graph()
		{
			vertice *tempv;
			vertice *prev_v;
			edge *tempe;
			edge *prev_e;

			cout << "Destructor Start" << endl;
			tempv = vertices;

			while (tempv != NULL) {
				tempe = tempv->edges;

				while (tempe != NULL) {
					prev_e = tempe;
					// next edge
					tempe = tempe->next;
					delete prev_e;
				}

				prev_v = tempv;
				// next vertice
				tempv = tempv->next;
				delete prev_v;
			}
			vertices = NULL;

			cout << "Destructor End" << endl;
		}
	
		vertice* add_vertice(int data);

		bool
		add_edge(int from, int to)
		{
			return add_edge(from, to, 0);
		}

		bool
		add_edge(int from, int to, int weight)
		{
			vertice *from_vertice;
			vertice *to_vertice;
			vertice *temp_vertice;
			edge *new_edge;
			edge *temp;
			unsigned int add_new_edge = (directed ? 1 : 2);

			from_vertice = find_vertice(from);
			if (from_vertice == NULL) {
				printf("From vertice %d present, adding it ...\n", from);

				from_vertice = add_vertice(from);
				if (from_vertice == NULL) {
					printf("Error: Unable to add a new_vertice %d \n", from);
					return false;
				}
			}

			to_vertice = find_vertice(to);
			if (to_vertice == NULL) {
				printf("To vertice %d not present, adding it ... \n", to);

				to_vertice = add_vertice(to);
				if (to_vertice == NULL) {
					printf("Error: Unable to add a new_vertice %d \n", to);
					return false;
				}
			}


			while (add_new_edge > 0) {
				printf("Adding edge: %d -> %d : %d (w)).\n",
						from_vertice->node, to_vertice->node, weight);
			
				// No loops in the graph.
				assert(to_vertice != from_vertice);

				// get the new edge.
				new_edge = get_new_edge(to_vertice, weight);
				if (new_edge == NULL) {
					printf("Error: Unable to get a new edge(%d -> %d : %d (w))\n",
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
						printf("Edge %d -> %d already present : %d (w)\n",
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
				//printf("Edge: %d -> %d : %d (w)) added.\n",
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
		edge_present_in_vertice(vertice *v, int edge_val)
		{
			edge *e;

			assert(v);

			if (v->edge_count == 0) {
				return false;
			}

			e = v->edges;

			while(e != NULL) {
				if (e->vertice->node == edge_val) {
					printf("edge_present_in_vertice: %d -> %d\n", v->node, edge_val);
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
			printf("\tGraph File: %s\n", graph_file);

			printf("Vertices and Edges:\n");

			tempv = vertices;
			while (tempv != NULL) {
				tempe = tempv->edges;

				printf("[%d]: ", tempv->node);
				while (tempe != NULL) {
					printf("--{%d}-> (%d) ", tempe->weight, tempe->vertice->node);
					// next edge
					tempe = tempe->next;
				}
				printf("\n");

				// next vertice
				tempv = tempv->next;
			}
		}

		void
		mst_prim(int from)
		{
			vertice *v_from, *v_temp;
			vertice *v; // temp vertice pointer
			edge *e; // temp edge pointer
			int distance;

			cout << "MST: Start" << endl;
			cout << "Finding MST from [" << from << "] " << endl;

			// init all the vertices for dijkistra shortest path.
			init_for_mst();

			// get start and end vertices.
			v_from = find_vertice(from);
			if (v_from == NULL) {
				cout << "Error: Vertex " << from << " not present." << endl;
				return;
			}

			// starting vertex - distance is 'zero'.
			v_from->sp.distance = 0;

			// starting vertex.
			v = v_from;

			cout << "MST:" << endl;

			while (!vertex_visited(v)) {
				vertex_mark_visited(v);

				if (v != v_from) {
					cout << get_vertex_value(v->sp.p) << " -> " <<
						 get_vertex_value(v) << endl;
				}

				e = v->edges;

				while (e != NULL) {
					if ((vertex_distance(e->vertice) > edge_weight(e)) &&
						!vertex_visited(e->vertice)) {
						e->vertice->sp.distance = edge_weight(e);
						e->vertice->sp.p = v;
					}
					e = e->next;
				} // end of while - edges
				
				// find the next vertex whose distance is minimum and who is not already visited.
				distance = INT_MAX;
				v_temp = vertices;
				v = v_from;

				while (v_temp != NULL) {
					// if the vertex is not already visited and the distance is more than
					// the distance of the current 'v_temp' vertex from the starting vertex
					// then select this vertex.
					if (!vertex_visited(v_temp) &&
						(distance > vertex_distance(v_temp))) {

						distance = vertex_distance(v_temp);
						v = v_temp;
		
					}
					v_temp = v_temp->next;
				}
			} // end of while.
			cout << endl;

			cout << "MST: End" << endl;

		}

		void
		dijkistra(int from, int to)
		{
			vertice *v_from, *v_temp;
			vertice *v_to;
			vertice *v; // temp vertice pointer
			edge *e; // temp edge pointer
			int distance;

			cout << "dijkistra: Start" << endl;
			cout << "Finding shortest path from [" << from <<
					"] to [" << to << "]" << endl;

			// init all the vertices for dijkistra shortest path.
			init_for_dijkistra();

			// get start and end vertices.
			v_from = find_vertice(from);
			assert(v_from);

			v_to = find_vertice(to);
			assert(v_to);

			// distance of starting to starting is always 'zero'.
			v_from->sp.distance = 0;

			// starting vertex.
			v = v_from;

			while (!vertex_visited(v)) {
				vertex_mark_visited(v);

				// if destination is reached, print the path
				if (v == v_to) {
					break; // break the main while loop, the algo is done.
				}
				
				e = v->edges;

				while (e != NULL) {
					if (vertex_distance(e->vertice) >
						(vertex_distance(v) + edge_weight(e)) ) {
						e->vertice->sp.distance = vertex_distance(v) + edge_weight(e);
						e->vertice->sp.p = v;
					}
					e = e->next;
				} // end of while - edges
				
				// find the next vertex whose distance is minimum and who is not already visited.
				distance = INT_MAX;
				v_temp = vertices;
				v = v_from; // some sane initial value - if no new vertex is slected, this
							// will help break the while loop.

				while (v_temp != NULL) {
					// if the vertex is not already visited and the distance is more than
					// the distance of the current 'v_temp' vertex from the starting vertex
					// then select this vertex.
					if (!vertex_visited(v_temp) &&
						(distance > vertex_distance(v_temp))) {

						distance = vertex_distance(v_temp);
						v = v_temp;
		
					}
					v_temp = v_temp->next;
				}

			} // end of while.

			// print the path.
			v_temp = v_to;

			cout << "Shortest Path" << endl;
			while (v_temp != NULL) {
				cout << v_temp->node << " <- ";

				// follow the parent
				v_temp = v_temp->sp.p;

				if (v_temp == NULL) {
					cout << endl << "No shortest path found." << endl;
				}
				if (v_temp == v_from) {
					cout << v_temp->node << endl;
					break;
				}
			}

			cout << "dijkistra: End" << endl;
		}
};

/*
 * Add a vertice in the graph.
 */
graph::vertice*
graph::add_vertice(int data)
{
	vertice *temp;
	vertice *head = vertices;

	cout << "add_vertice [" << data << "] " << endl;

	if (find_vertice(data)) {
		printf("Error: vertice %d already present\n", data);
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
	//printf("Added vertex [%d]\n", new_vertice->node);
	cout << "[" << vertices_count <<"] Added vertex [" << data << "] " << endl;
	return new_vertice;
}

double
prob()
{
	double num;

	num = static_cast<double>(rand() % 100 + 1); // a number between 1 - 100

	return (num/100);
}

/*
 * create the graph : randomly
 */
void
graph::create_graph_randomly(void)
{
	int v;
	int t; // target vertex for a new edge.
	vertice *vertex;
	int w;
	double ed = (static_cast<double>(edge_density) / 100);

	if ((max_vertices == 0) || (edge_density == 0) || (weight_range == 0)) {
		cout << "Graph will be created manually" << endl;
		return;
	}

	cout << "Entry : create_graph_randomly, Edge Density: " << ed << endl << endl;

	// set the seed for rand()
	srand(time(0));


	// Add all the vertices.
	while (vertices_count != max_vertices) {
	
		// get a new vertex to add to the graph
		v = get_new_vertex_value();
		printf("[%d: %d] New Vertex: %d\n\n", vertices_count, max_vertices, v);

		if (find_vertice(v)) {
			// if the vertex is already present in the graph, continue.
			continue;
		}
		cout << "Adding vertex: " << v << endl;
		vertex = add_vertice(v);
		assert(vertex != NULL);
	}

	cout << "All [" << vertices_count << "] vertices created." << endl;

	vertice *tempv;
	int edges;

	tempv = vertices;

	while (tempv != NULL) {
		edges = 0;

		v = tempv->node;
		tempv = tempv->next;

		// re-set the seed for rand() for each vertex.
		srand(time(0));

		int idx;
		for (idx = 0; idx < vertices_count; idx++) {
			
			t = idx;

			if (v == t) {
				continue;
			}

			if (!find_vertice(t)) {
				// if some vertice in the range is not added, move to the next.
				continue;
			}

			// Do we want to add this edge per probability of edge density.
			// If not, move to the next possible edge.
			if (prob() > ed) {
				continue;
			}

			// if the edge is already present, move on ...
			if (edge_present_in_vertice(vertex, t)) {
				continue;
			}

			// get a weight to attach to the edge
			w = get_weight();
			cout << "[" << vertex->edge_count << ": ] " << v <<
				 " -> " << t << " " << w << " (w)." << endl;
			// add the edge
			add_edge(v, t, w);
		}
		cout << "Added " << edges << " edges to vertex " << v << endl;
	}

	edges = 0;
	tempv = vertices;
	while (tempv != NULL) {
		edges += tempv->edge_count;
		tempv = tempv->next;
	}

	cout << "Exit : create_graph_randomly with " << edges << " edges." << endl;
}

void
show_menu()
{
	printf("1. Add vertice\n");
	printf("2. Add Edge\n");
	printf("3. Display graph\n");
	printf("4. Shortest path\n");
	printf("5. Minimum Spanning Tree\n");
	printf("0. Exit\n");
	printf("Enter choice: ");
}

int
main(int argc, char **argv)
{
	bool is_directed = false;
	int num_vertices = 0;
	unsigned int e_density = 0;
	unsigned int w_range = 0;
	bool done = false;
	int value;
	int to, from;
	int w;
	char *in_file = NULL;

	if (argc == 1) {
		cout << "usage: ./a.out <number of vertices> "
				"<edge density> <range of edge weights>" << endl;
		return (-1);
	}

	// initialze the graph

	if (argc == 2) {
		// a graph file name must be given
		in_file = argv[1];
	} else if (argc == 4) {
		// count of vertices in the graph
		num_vertices = atoi(argv[1]);

		// density of edges
		e_density = atoi(argv[2]);

		// range of weights
		w_range = atoi(argv[3]);

	} else {
		cout << "usage: ./a.out <number of vertices> "
				"<edge density> <range of edge weights>" << endl;
		return (-1);
	}

	graph g(is_directed, num_vertices, e_density, w_range, in_file);

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

			case 5:
				printf("MST starting from: ");
				cin >> from;
				g.mst_prim(from);
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
