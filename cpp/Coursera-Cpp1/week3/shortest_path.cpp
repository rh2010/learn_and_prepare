#include <iostream>
#include <cstdbool>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <fstream>

using namespace std;

static inline double
prob()
{
	double p;
	p = (static_cast<double>(rand()) / RAND_MAX);

	return p;
}

// Class for representing a graph using adjacency list.
class graph {

	// init params for the graph
	const char *graph_file;
	const int max_vertices; // The number of vertices to which the graph should goto.
	int vertices_count; // the current vertex count in the graph 

	const unsigned int edge_density; // Edge density: ranges between 1 - 100.
							   // 11 -> .11 probability of an edge to exist in the graph.
							   // 23 -> .23 probability
							   // ...
							   // 100 -> 1 probability i.e. A Complete Graph .. all the edges are
                               // present in the graph.
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
		int node; // for storing data.
		int edge_count;
		bool is_visited;
		struct vertice *next;

		// edges can also be a hash-map for faster lookups.
		struct edge *edges;

		// book keeping data for shortest path
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
		return (rand() % get_max_vertex_count());
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
			cout <<"Error: Unable to get memory for vertice" << endl;
			return NULL;
		}

		// set the value of the vertice.
		v->node = value;
		v->edge_count = 0;
		v->next = NULL;
		v->edges = NULL;
		v->is_visited = false;
		v->sp.distance = INT_MAX; // INFINITY
		v->sp.p = NULL; // parent is NULL

		return v;
	}

	// the vertice will be the to vertice.
	edge*
	get_new_edge(vertice* vertice, int weight)
	{
		edge *e = new edge;
		if (e == NULL) {
			cout << "Error: Unable to allocate memory for edge\n";
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
				return temp;
			}
			temp = temp->next;
		}
		assert(temp == NULL);

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
			cout << "Graph File: " << (this->graph_file?this->graph_file:"NULL") << endl << endl;
			
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
		edge_density(2), // default edge density : 20%
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

				from_vertice = add_vertice(from);
				if (from_vertice == NULL) {
					cout << "Error: Unable to add a new_vertice " << from << endl;
					return false;
				}
			}

			to_vertice = find_vertice(to);
			if (to_vertice == NULL) {

				to_vertice = add_vertice(to);
				if (to_vertice == NULL) {
					cout << "Error: Unable to add a new_vertice " << to << endl;
					return false;
				}
			}


			while (add_new_edge > 0) {
				// No loops in the graph.
				assert(to_vertice != from_vertice);

				// get the new edge.
				new_edge = get_new_edge(to_vertice, weight);
				if (new_edge == NULL) {
					cout << "Error: Unable to get a new edge(" << from << 
							" -> " << to << " :  (" << weight << ")" << endl;
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

			cout << "Graph:\n";
			cout << "\tVertices count: " << vertices_count << endl;
			cout << "\t" << (directed ? "Directed" : "Un-directed") << endl;
			cout << "\tMax Vertices count: " << max_vertices << endl;
			cout << "\tEdge density: " << edge_density << endl;
			cout << "\tWeight range: " << weight_range << endl;
			cout << "\tGraph File: " << (graph_file ? graph_file : "Null") << endl;

			cout << "Vertices and Edges:" << endl;

			tempv = vertices;
			while (tempv != NULL) {
				tempe = tempv->edges;

				cout << "["<< tempv->node <<"]: ";
				while (tempe != NULL) {
					cout << "--{"<< tempe->weight <<"}-> ("<<
						 tempe->vertice->node << ") ";
					// next edge
					tempe = tempe->next;
				}
				cout << endl;

				// next vertice
				tempv = tempv->next;
			}
		}

		/*
		 * Return the path length for the shortest path found.
		 * Else, return -1 for no path found to the destination node.
		 */
		int
		dijkistra(int from, int to)
		{
			vertice *v_from, *v_temp;
			vertice *v_to;
			vertice *v; // temp vertice pointer
			edge *e; // temp edge pointer
			int distance;

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
			int path_length = 0;

			cout << "Shortest Path" << endl;
			while (v_temp != NULL) {
				cout << v_temp->node << " <- ";

				// follow the parent
				v_temp = v_temp->sp.p;

				// increment for each hop made.
				path_length++;

				if (v_temp == NULL) {
					cout << endl << "No shortest path found." << endl;
					return (-1);
				}
				if (v_temp == v_from) {
					cout << v_temp->node << endl;
					break;
				}
			}

			return path_length;
		}

		int
		get_vertice_count(void)
		{
			return vertices_count;
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


	if (find_vertice(data)) {
		cout << "Error: vertice " << data << " already present\n";
		return NULL;
	}

	vertice *new_vertice = get_new_vertice(data);
	if (new_vertice == NULL) {
		cout << "Error: Failed to get a new vertice\n";
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
	return new_vertice;
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

	int idx;
	// Add all the vertices.
	for (idx = 1; idx <= max_vertices; idx++) {
	
		// get a new vertex to add to the graph
		v = idx;

		if (find_vertice(v)) {
			// if the vertex is already present in the graph, continue.
			continue;
		}

		vertex = add_vertice(v);
		assert(vertex != NULL);
	}

	assert (vertices_count == max_vertices);

	vertice *tempv;
	int edges;

	tempv = vertices;
	while (tempv != NULL) {
		edges = 0;

		v = tempv->node;
		tempv = tempv->next;

		// re-set the seed for rand() for each vertex.
		srand(time(0));

		for (idx = 1; idx <= vertices_count; idx++) {

			t = idx;

			if (v == t) {
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

			// add the edge
			add_edge(v, t, w);
		}
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
	cout << "1. Add vertice\n";
	cout << "2. Add Edge\n";
	cout << "3. Display graph\n";
	cout << "4. Shortest path\n";
	cout << "5. Homework Week3\n";
	cout << "0. Exit\n";
	cout << "Enter choice: ";
}

int
main(int argc, char **argv)
{
	bool is_directed = false;
	int num_vertices;
	unsigned int e_density;
	unsigned int w_range;
	bool done = false;
	int value;
	int to, from;
	int w;
	char *in_file = NULL;

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
		exit(-1);

	}

	graph g(is_directed, num_vertices, e_density, w_range, in_file);
	int choice;

	while(!done) {

		show_menu();

		cin >> choice;

		switch (choice) {
			case 1:
				cout << "Vertice to add: ";
				cin >> value;
				g.add_vertice(value);
				break;

			case 2:
				cout << "Edge to add (from, to): ";
				cin >> from >> to >> w;
				g.add_edge(from, to, w);
				break;

			case 3:
				g.show();
				break;

			case 4:
				cout << "Shortest path between (from, to): ";
				cin >> from >> to;
				cout << "( " << from << ", " << to << ")" << endl;
				g.dijkistra(from, to);
				break;

			case 5:
				cout << "Homework Week 3";
				int idx;
				int path_length;
				int sum;
				int count;

				from = 1; // starting node.
				count = 0; // to count how many nodes we can reach
				sum = 0;
				for (idx = from+1; idx <= g.get_vertice_count(); idx++) {
					// idx is the to node.
					path_length = g.dijkistra(from, idx);
					// path_length -1 means there is not path from 'from' to
					// 'idx'
					if (path_length != -1) {
						cout << "Shortest path length from " << from <<
							 " to " << idx << ": " << path_length << endl;
						sum += path_length;
						count++;
					}

				}
				cout << "Average path length: " << (static_cast<double>(sum))/count << endl;

				break;

			case 0:
				done = true;
				cout << "Exiting ...\n";
				break;
			default:
				cout << "Unknown option, try again\n";
				break;
		}
	}

	return (0);
}
