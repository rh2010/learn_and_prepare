#include <iostream>
#include <cstdbool>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <queue>
#include <unordered_map>

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

	// pointer to the other vertice which this edge consists of.
	struct vertice *vertice;
};

// A comparator class for edge.
class edge_comparator {
	public:
	// overload ()
	bool operator()(const edge* e1, const edge* e2)
	{
		return (e1->weight > e2->weight);
	}
};

// An vertice
//
// A vertice in the graph.
struct vertice {
	int node; // for storing data.
	int edge_count;
	bool is_visited;
	struct vertice *next;

	priority_queue<edge*, vector<edge*>, edge_comparator> edges;

	// lookup key is the target vertice value
	unordered_map<int, edge*> edges_map;

	// book keeping data for shortest path
	struct sp {
		int distance;
		struct vertice *p;
	} sp;
};

//
// Class for representing a graph using adjacency list.
class graph {

	// init params for the graph
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
		v->is_visited = false;
		v->sp.distance = INT_MAX; // INFINITY
		v->sp.p = NULL; // parent is NULL

		// edges : a Priority Queue for lookup by smallest edge-weight.
		// edges_map : A hash for quick lookup of edges by destination vertex.
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

		return e;
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

	void
	create_graph_randomly(void);

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

		assert(vertices.size() > 0);

		for (auto it = vertices.begin(); it != vertices.end(); it++) {
		    temp = it->second;

			temp->is_visited = false;
			temp->sp.distance = INT_MAX;
			temp->sp.p = NULL;
		}
	}

	public:
		// constructor
		graph(bool is_directed,
			  int num_vertices,
			  unsigned int edge_density,
			  unsigned int weight_range)
			  :max_vertices(num_vertices),
			  directed(is_directed),
			  edge_density(edge_density),
			  weight_range(weight_range)
		{
			vertices_count = 0;

			// Create the graph randomly from input parameters.
			cout << "Creating graph with params" << endl;
			cout << "is_directed: " << directed << endl;
			cout << "Maximum vertices: " << max_vertices << endl;
			cout << "Edge density: " << this->edge_density << endl;
			cout << "Weight Range: " << this->weight_range << endl << endl;

			vertices.reserve(max_vertices);

			create_graph_randomly();
		}

		// default constructor
		graph()
		:vertices_count(0),
		max_vertices(0),
		directed(false),
		edge_density(2), // default edge density : 20%
		weight_range(10) // default range is 1 - 10
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

				while (!tempv->edges.empty()) {
					tempe = tempv->edges.top();
					tempv->edges.pop();
					delete tempe;
				}
				tempv->edges_map.clear();
			}
			vertices.clear();
		}

		// forward declaration of add_vertice method
		vertice* add_vertice(int data);

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
				new_edge = get_new_edge(to_vertice, weight);
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
				from_vertice->edges.push(new_edge);
				from_vertice->edges_map.insert({to, new_edge});

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


		/*
		 * Return the path length for the shortest path found.
		 * Else, return -1 for no path found to the destination node.
		 */
		/*
		int
		dijkistra(int from, int to)
		{
			vertice *v_from, *v_temp;
			vertice *v_to;
			vertice *v; // temp vertice pointer
			edge *e; // temp edge pointer
			int distance;

			// TODO:
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

			while (v_temp != NULL) {

				// follow the parent
				v_temp = v_temp->sp.p;

				// increment for each hop made.
				path_length++;

				if (v_temp == NULL) {
					cout << endl << "No shortest path found." << endl;
					return (-1);
				}
				if (v_temp == v_from) {
					break;
				}
			}

			return path_length;
		}
		*/

		int
		get_vertice_count(void)
		{
			return vertices.size();
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

	graph g(is_directed, num_vertices, e_density, w_range);
/*
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
			sum += path_length;
			count++;
		}

	}
	cout << "Average path length: " << (static_cast<double>(sum))/count << endl;
*/
	return (0);
}
