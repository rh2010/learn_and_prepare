#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

#define SFHC_OBSERVER(x) (dynamic_cast<derived*>(x))
#define MAX_RANGE (4999)

/*
const int max_val = 52;

inline
int r_sides()
{
	return (rand() % max_val);
}

char
get_new_vertex_value(void)
{
	int rand_val = r_sides();
	char val;

	if (rand_val < 26) {
		cout << "Upper ";
		val = static_cast<char>('A' + rand_val);
	} else {
		cout << "Lower ";
		val = static_cast<char>('a' + (rand_val - 26));
	}
	cout << ": " << rand_val << "-> " << val << endl;

	return val;
}

int
main (void)
{
	const int n_dice = 2;
	int d1, d2;

	// set the seed for rand()
	srand(clock());

	cout << "A + 0 -> " << static_cast<char>('A' + 0) << endl;
	cout << "A + 1 -> " << static_cast<char>('A' + 1) << endl;
	cout << "A + 2 -> " << static_cast<char>('A' + 25) << endl;
	cout << "a + 0 -> " << static_cast<char>('a' + 0) << endl;
	cout << "a + 1 -> " << static_cast<char>('a' + 1) << endl;
	cout << "a + 2 -> " << static_cast<char>('a' + 25) << endl;


	cout << "\nEnter the number of trials: ";

	int trials;
	cin >> trials;


	for (int j = 0; j < trials; ++j) {
		get_new_vertex_value();
	}

	return (0);
}*/

class base {
public:
    base () {
        cout << "Ctor of base" << endl;
    }

    ~base () {
        cout << "Dtor base" << endl;
    }

    void b(int i) {
        cout << "base::b " << i << endl;
        e(i);
    }
    void SendMsg(const string& s="")
    {
        if (s.empty()) {
            cout << "String is empty." << endl; 
        } else {
            cout << "String is: (" << s << ")." << endl;
        }
    }
    virtual void get_uuid() {
        cout << "Base get_uuid" << endl;
    }
private:
    virtual void e(int i) {
        cout << "base::e " << i << endl;
    }
};

class derived : public base {
public:
    derived () : msg(1) {
        cout << "Ctor of derived" << endl;
    }

    ~derived () {
        cout << "Dtor derived" << endl;
    }

    void f(int i) {
        cout << "derived:f " << i << endl;
        e(i);
    }
    void c(int i) {
        cout << "derived:c " << i << endl;
    }
    void d(int i) {
        cout << "derived:d " << i << endl;
    }
    virtual void e(int i) {
        cout << "derived::e " << i << endl;
    }
    void get_uuid() {
        cout << "Derived get_uuid" << endl;
    }

	int msg;
};

double
prob(void)
{
	return (static_cast<double>(rand())/RAND_MAX);
}

#define TRACEFLOW "com.vmware.com.Traceflow"
#define SB "com.vmware.com.SupportBundle"

struct bsons {
    bsons(int *h, int *w)
    : header(h)
    , wrapper(w)
    {
        cout << "bsons ctor" << endl;
    }

    ~bsons() {
        cout << "bsons Dtor begin" << endl;
        delete header;
        delete wrapper;
        cout << "bsons Dtor end" << endl;
    }

    int *header;
    int *wrapper;
};

void set_type(string &t)
{
    cout << "t: " << t << endl;
    string str("Rohit");
    t = str;
    cout << "t: " << t << endl;
}

void
foo(base* b)
{
	cout << "foo: " << SFHC_OBSERVER(b)->msg << endl;
}

int
main(void)
{
	/*int i = 9, j = 3;
	int edge_density = 45;
	double ed;
	
	cout << "I is "<< i << ", J is " << j << endl;

	{
		int i = j + 2;
		cout << "I is "<< i << ", J is " << j << endl;
	}
	cout << "I is "<< i << ", J is " << j << endl;


	srand(time(0));

	// random probability generation
	for (i = 0; i < 10; i++) {
		cout << prob() << ", ";
	}
	cout << endl;

	ed = static_cast<double>(edge_density / 100);
	cout << "ed1: " << ed << endl;
	ed = (static_cast<double>(edge_density) / 100);
	cout << "ed2: " << ed << endl;

    base* b = new base;
    derived* d = new derived;
    base* b2 = d;

    cout << "Test Derived Begin" << endl;
    d->get_uuid();
    b2->get_uuid();
    cout << "Test Derived End" << endl;
    b->b(11);
    b->SendMsg(); // Empty string
    b->SendMsg("Test SendMsg");
    d->b(99);

    cout << "Test bsons Begin" << endl;

    int *val1 = new int;
    int *val2 = new int;

    bsons *bsonsPtr = new bsons(val1, val2);

    void *msgBuf = (void*)bsonsPtr;
    //free(msgBuf);
    delete bsonsPtr;
    cout << "Test bsons End" << endl;
    */
    //b.a(1);
    //b.b(2);
    //b.e(9);

    //d.a(3);
    //d.b(4);
    //d.c(5);
    //d.d(6);
    //d.f(7);
	//
	derived* d = new derived;
	foo(d);
    //cout << "==== String ======" << endl;
    //string name = "";
    //set_type(name);
    //cout << "Name: " << name << endl;
	/*
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	int iter = 0;

	while (iter++ < v.size()) {
		cout << "iter: " << iter << endl;
	}

	iter = 0;
	while (++iter < v.size()) {
		cout << "iter: " << iter << endl;
	}

	for (iter = 0; iter < v.size(); ++iter) 
		cout << "iter: " << iter << endl;

	for (iter = 0; iter < v.size(); iter++) 
		cout << "iter: " << iter << endl;
	*/
	string s("abracadabra");

	printf("s: %s\n", s.c_str());
	printf("s 0: %s", s.substr(0, 0).c_str());
	printf("s 0-1: %s", s.substr(0, 1).c_str());
	printf("s 0-2: %s", s.substr(0, 2).c_str());
	printf("s 0-3: %s\n", s.substr(0, 3).c_str());

	vector<char> line = {'.', '3', '.', '5'};
	int num = 3;
	int num2 = 9;
	//printf("is three: %d, (%c)\n", (line[1]==itoa(num)), line[1]);
	printf("is five: %d, (%c)\n", (line[3]==(char)num), line[3]);
	printf("is empty: %d\n", (line[0]=='.'));
	printf("1) %d\n", line[1]-'0');
	line[2] = num2+'0';
	printf("2) %d\n", line[2]-'0');
	return (0);
}

