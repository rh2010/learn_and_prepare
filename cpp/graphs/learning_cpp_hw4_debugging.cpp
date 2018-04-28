#include <iostream>
#include <cstdbool>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <queue>

using namespace std;

static inline double
prob()
{
	double p;
	p = (static_cast<double>(rand()) / RAND_MAX);

	return p;
}

struct vertice;

// An edge in the graph.
struct edge {
	int weight; // an edge might or might not have a weight associated with it.
	int from;
	int to;

	// pointer to the other vertice which this edge consists of.
	struct vertice *vertice;
};

// An vertice
//
// A vertice in the graph.
struct vertice {
	int node; // for storing data.
	int edge_count;
	bool is_visited;
	struct vertice *next;

	// lookup key is the target vertice value
	unordered_map<int, edge*> edges_map;
};

// A comparator class for vertice distance.
class edge_cost {
	public:
	// overload ()
	bool operator()(const edge* e1, const edge* e2)
	{
		return (e1->weight > e2->weight);
	}
};

//
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

	unordered_map<int, vertice*> vertices;

	int
	get_max_vertex_count(void)
	{
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
		// return a random value between 1 - 10.
		return ((rand() % weight_range) + 1);
	}

	int
	get_new_vertex_value(void)
	{
		return (rand() % get_max_vertex_count());
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
		v->edge_count = 0; // this can come from edges_map.size()
		v->next = NULL;
		v->is_visited = false;

		// edges_map : A hash for quick lookup of edges by destination vertex.
		return v;
	}

	// the vertice will be the to vertice.
	edge*
	get_new_edge(vertice* from_vertice, vertice* to_vertice, int weight)
	{
		edge *e = new edge;
		if (e == NULL) {
			cout << "Error: Unable to allocate memory for edge\n";
			return NULL;
		}

		e->from = from_vertice->node;
		e->to = to_vertice->node;
		e->vertice = to_vertice;
		e->weight = weight;

		return e;
	}

	void
	create_graph_randomly(void);

	void
	add_edge_to_vertice(vertice *v, edge* e)
	{
		assert(e);
		assert(v);

		v->edges_map.insert({e->vertice->node, e});
	}

	void
	build_graph_from_file(const char *file_name)
	{
		int s, t, w;
		int num_vertices;

		assert(file_name != NULL);

		// open the file to read the i/p graph
		ifstream graph_file(file_name);

		// get the vertex count
		graph_file >> num_vertices;

		vertices.reserve(num_vertices);

		// add the edges
		while (graph_file >> s >> t >> w) {
			add_edge(s, t, w);
		}
		assert(num_vertices == vertices_count);

		cout << "Max vertices: " << num_vertices << ", vertices added: " <<
			 vertices_count << endl;
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

			// Create the graph randomly from input parameters.
			cout << "Creating graph with params" << endl;
			cout << "is_directed: " << directed << endl;
			cout << "Maximum vertices: " << max_vertices << endl;
			cout << "Edge density: " << this->edge_density << endl;
			cout << "Weight Range: " << this->weight_range << endl << endl;

			if (graph_file) { 
				build_graph_from_file(this->graph_file);
			} else {
				vertices.reserve(max_vertices);
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
		}

		~graph()
		{
			vertice *tempv;
			vertice *prev_v;
			edge *tempe;
			edge *prev_e;

			for (auto it = vertices.begin(); it != vertices.end(); it++) {
				tempv = it->second;

				for (auto it_e = tempv->edges_map.begin();
					 it_e != tempv->edges_map.end(); it_e++) {

					tempe = it_e->second;
					delete tempe;
				}
				tempv->edges_map.clear();
			}
			vertices.clear();
		}

		// forward declaration of add_vertice method
		vertice* add_vertice(int data);

		int
		get_vertex_value(vertice *v)
		{
			assert(v != NULL);

			return v->node;
		}

		bool
		edge_present_in_vertice(vertice *v, int to_vertex_val)
		{
			bool ret = false;

			if (v->edges_map.count(to_vertex_val) > 0) {
				assert(v->edges_map.count(to_vertex_val) == 1);
				ret = true;
			}
			return ret;
		}

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
				new_edge = get_new_edge(from_vertice, to_vertice, weight);
				if (new_edge == NULL) {
					cout << "Error: Unable to get a new edge(" << from <<
							" -> " << to << " :  (" << weight << ")" << endl;
					return false;
				}

				// No loops in the graph.
				assert(new_edge->vertice != from_vertice);

				// check, if the edge is already present.
				if (edge_present_in_vertice(from_vertice, to)) {
					//cout << "Edge " << from << " -> " << to << " already "
					//		"present : " << weight << " (w)" << endl;

					// free up the new edge.
					delete(new_edge);
					return false;
				}

				// add the new edge to the list
				add_edge_to_vertice(from_vertice, new_edge);
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

		int
		get_vertice_count(void)
		{
			return vertices.size();
		}

		inline void
		vertex_mark_visited(vertice *v)
		{
			assert(v);
			v->is_visited = true;
		}

		int
		edge_weight(edge *e)
		{
			assert(e);
			return e->weight;
		}

		inline bool
		vertex_visited(vertice *v)
		{
			assert(v);

			return v->is_visited;
		}

		void
		init_for_prim(void)
		{
			vertice *temp;

			assert(vertices.size() > 0);

			for (auto it = vertices.begin(); it != vertices.end(); it++) {
			    temp = it->second;
				temp->is_visited = false;
			}
		}

		vertice*
		find_vertice(int value)
		{
			vertice *temp = NULL;

			if (vertices.count(value) > 0) {
				temp = vertices[value];
			}
			return temp;
		}

		//
		// Check if the resulting tree is a MST or not.
		// Check if all the vertices are visited or not.
		//
		bool
		check_mst(void)
		{
			vertice* v;

			for (auto it = vertices.begin(); it != vertices.end(); it++) {
				v = it->second;
				if (!vertex_visited(v)) {
					return false;
				}
			}
			return true;
		}

		int
		get_edge_cost(vertice* f, vertice* t)
		{
			int to;
			edge* e;

			assert(f);
			assert(t);

			if (f->edges_map.count(t->node) > 0) {
				assert(f->edges_map.count(t->node) == 1);
				e = f->edges_map[t->node];
				return e->weight;
			}
			return -1;
		}
};

/*
 * Add a vertice in the graph.
 */
vertice*
graph::add_vertice(int data)
{
	vertice *temp;

	if (find_vertice(data)) {
		cout << "Error: vertice " << data << " already present\n";
		return NULL;
	}

	vertice *new_vertice = get_new_vertice(data);
	if (new_vertice == NULL) {
		cout << "Error: Failed to get a new vertice\n";
		exit(-1);
	}

	// add the new_vertice in the list
	vertices.insert({data, new_vertice});

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

	assert (vertices.size() == max_vertices);
	assert (vertices.size() == vertices_count);

	vertice *tempv;
	int edges;

	// Add edges, for every vertex added.
	for (auto it = vertices.begin(); it != vertices.end(); it++) {
		tempv = it->second;

		v = tempv->node;

		// re-set the seed for rand() for each vertex.
		srand(time(0));

		for (idx = 1; idx <= vertices.size(); idx++) {

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

	for (auto it = vertices.begin(); it != vertices.end(); it++) {
		tempv = it->second;
		edges += tempv->edge_count;
	}

	cout << "Exit : create_graph_randomly with " << edges << " edges." << endl;
}

class mst : public graph {
	public:
		// constructor
		// this will initialize the graph.
		mst(bool is_directed,
			  		int num_vertices,
			  		unsigned int edge_density,
			  		unsigned int weight_range,
					char *file)
					: graph(is_directed,
							num_vertices,
							edge_density,
							weight_range,
							file)
		{
		}

		// default constructor
		mst()
		{
		}

		// destructor
		~mst()
		{
		}

		void
		show(queue<edge*>* tree)
		{
			edge* e;
			vertice* v;

			if (tree == NULL) {
				cout << "No MST\n";
				return;
			}

			int cost = 0;
			cout << "MST Tree: " << endl;

			while (!tree->empty()) {
				e = tree->front();
				cost += edge_weight(e);
				cout << e->from << " -> " << e->to << " [" << edge_weight(e) << "]" << endl;
				tree->pop();
			}
			cout << "MST Cost: " << cost << endl;
		}

		/*
		 * Return the path length for the shortest path found.
		 * Else, return -1 for no path found to the destination node.
		 */
		queue<edge*>*
		prim(int from)
		{
			vertice *v_from, *v_temp;
			vertice *v; // temp vertice pointer
			edge *e; // temp edge pointer
			int distance;

			queue<edge*>* q;
			q = new queue<edge*>;

			// init all the vertices for dijkistra shortest path.
			init_for_prim();

			// get start and end vertices.
			v_from = find_vertice(from);
			assert(v_from);

			// starting vertex.
			v = v_from;

			priority_queue<edge*, vector<edge*>, edge_cost> cost_min_heap;

			int cost = 0;
			while (!vertex_visited(v)) {
				vertex_mark_visited(v);
				cout << "\nProcessing [" << v->node << "] \n------------------\n\n";

				for (auto it = v->edges_map.begin(); it != v->edges_map.end(); it++) {
					e = it->second;

					// don't process if the vertex is already visited.
					if (vertex_visited(e->vertice)) {
						continue;
					}

					// add to PQ
					cout << "Push: " << e->from << " -> " << e->to << " ["
						 << edge_weight(e) << "]" << endl;
					cost_min_heap.push(e);
				}

				if (cost_min_heap.empty()) {
					cout << "Min heap is empty." << endl;
					break;
				}

				// select the edge with minimum weight and whose starting
				// vertice is not already visited.
				do {
					e = cost_min_heap.top();
					cost_min_heap.pop();
					cout << "Removed: " << e->from << " -> " << e->to << " ["
						 << edge_weight(e) << "]" << endl;
				} while(!cost_min_heap.empty() && vertex_visited(e->vertice));
				cout << "Next: " << e->from << " -> " << e->to << " ["
					 << edge_weight(e) << "]" << endl;
				v = e->vertice;

				// add the edge to the queue.
				if (!vertex_visited(e->vertice)) {
					cout << "Sol Add: " << e->from << " -> " << e->to << " ["
						 << edge_weight(e) << "]" << endl;
					q->push(e);
				}

			} // end of while.

			if (!check_mst()) {
				cout << "Not a connected graph, didn't produce a MST\n";
				delete q;
				q = NULL;
			}

			cout << "Cost: " << cost << endl << endl;
			return q; // return the path as a queue.
		}
};

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

	// initialze the graph
	if (argc == 2) {
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

	mst g(is_directed, num_vertices, e_density, w_range, in_file);

	char choice = 'n';
	queue<edge*>* mst_tree;

	do {
		cout << "MST starting from: ";
		cin >> from;
		mst_tree = g.prim(from);
		g.show(mst_tree);
		//cout << "Continue: ";
		//cin >> choice;
	} while(choice =='y');
	cout << "Done ..." << endl;

	return (0);
}
