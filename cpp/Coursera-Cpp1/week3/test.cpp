#include <iostream>
#include <queue>
#include <unordered_map>
#include <stack>
#include <queue>

using namespace std;

//
// test priority queues
//

class edge_comparator {
	public:
	bool operator()(const int& a, const int& b)
	{
		return (a > b);
	}
};


struct vertice {
	int data;

};

int
main(void)
{
	// overload ()
	priority_queue<int, vector<int>, edge_comparator> edges;
	priority_queue<int> edges_2;

	edges.push(3);
	edges.push(5);
	edges.push(1);
	edges.push(9);
	edges.push(11);

	while (!edges.empty()) {
		cout << edges.top() << endl;
		edges.pop();
	}
	cout << "Done PQ" << endl;

	// declare an unordered map
	//
	// the key is int
	// the value of of type vertice
	unordered_map<int, vertice*> vertices;
	vertices.reserve(50);
	
	vertice *v = new vertice;
	v->data = 3;

	vertices.insert({v->data, v});

	v = new vertice;
	v->data = 7;
	vertices.insert({v->data, v});

	cout << "Map size: " << vertices.size() << endl;

	vertice *t;

	vertices.find(3);

	int val;

	val = 4;

	// -ve test
	if (vertices.count(val) > 0) {
		t = vertices[val];
		cout << "Vertice " << t->data << " found in map" << endl;
	} else {
		t = NULL;
		cout << "Value " << val << "not in map" << endl;
	}

	val = 3;

	if (vertices.count(val) > 0) {
		t = vertices[val];
		cout << "Vertice " << t->data << " found in map" << endl;
	} else {
		t = NULL;
		cout << "Value " << val << "not in map" << endl;
	}

	// iterators in map.
	cout << "map iterator begin" << endl;
	for (auto it = vertices.begin(); it != vertices.end(); it++) {
		t = it->second;
		cout << t->data << endl;
	}
	cout << "map iterator end" << endl;

	cout << "Stack ... start\n";

	stack<int>* s;

	s = new stack<int>;

	s->push(1);
	s->push(2);
	s->push(3);

	cout << "Stack size: " << s->size() << endl;

	while (!s->empty()) {
		cout << s->top() << endl;
		s->pop();
	}

	delete s;
	cout << "Stack ... end\n";

	cout << "Queue ... start\n";

	queue<int>* q;
	q = new queue<int>;

	q->push(1);
	q->push(2);
	q->push(3);

	cout << q->size() << " elements in Queue\n";

	while (!q->empty()) {
		cout << q->front() << endl;
		q->pop();
	}
	delete q;

	cout << "Queue ... end\n";
}
