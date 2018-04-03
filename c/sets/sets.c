#include "../util.h"
#include <time.h>
#include <stdbool.h>

/*
 * Implement APIs to implement Sets.
 *
 *  - make_set - Create a set with the a single element.
 *  - find - Find which set an element belongs to.
 *  - union - Perform a join of two sets.
 *
 *
 *  Approaches:-
 *
 *  1) Tree based approach with rank
 *  2) Rank based approach
 *  3) Rank based approach with path compression.
 *
 *  Implement :-
 *  a) A tree based approach with rank
 *  b) Add path compression to approach b)
 */

struct set {
	int size;
	int *parent; // this give the tree formation.
	int *rank; // stores the rank for each root
};

// set interfaces
//
// interfaces for approach a)
void set_init(struct set *s, int size);
void set_uninit(struct set *s);
bool is_same_set(struct set *s, int key1, int key2);
void make_set(struct set *s, int key);
int find(struct set *s, int key);
void set_union(struct set *s, int key1, int key2);

// interfaces for approach b)
void make_set_pc(struct set *s, int key);
int find_pc(struct set *s, int key);
void set_union_pc(struct set *s, int key1, int key2);

/*
 * Initialize a set.
 */
void
set_init(struct set *s, int size)
{
	assert(s != NULL);

	s->size = size;

	// init parent array
	s->parent = (int *)malloc(sizeof (int) * size);
	assert(s->parent != NULL);
	memset(s->parent, 0, sizeof(int)*size);

	// init rank array
	s->rank = (int *)malloc(sizeof (int) * size);
	assert(s->rank != NULL);
	memset(s->rank, 0, sizeof(int)*size);
}

/*
 * Un-initialize / clean-up a set.
 */
void
set_uninit(struct set *s)
{
	assert(s != NULL);

	free(s->parent);
	free(s->rank);
	s->size = 0;
}

/*
 * Dump a set - for debugging
 */
void
set_dump(struct set *s)
{
	int i;
	assert(s != NULL);

	printf("Dump Set:\n");
	printf("\tsize: %d\n", s->size);
	printf("\tindex: ");
	for (i=0; i<s->size; i++) {
		printf("%d ", i);
	}
	printf("\n");

	printf("\tp    : ");
	for (i=0; i<s->size; i++) {
		printf("%d ", s->parent[i]);
	}
	printf("\n");

	printf("\trank : ");
	for (i=0; i<s->size; i++) {
		printf("%d ", s->rank[i]);
	}
	printf("\n");
	printf("\n");
}

void
set_build(struct set *s)
{
	int i;
	assert(s != NULL);

	for (i=0; i<s->size; i++) {
		make_set(s, i);
	}
}

/*
 *
 *  make_set - Create a set with the a single element.
 */
void
make_set(struct set *s, int key)
{
	assert(s != NULL);

	s->parent[key] = key;
	s->rank[key] = 0;
}

/*
 *  Find which set an element belongs to.
 */
int
find(struct set *s, int key)
{
	assert(s != NULL);

	while (key != s->parent[key]) {
		key = s->parent[key];
	}
    return key;
}

bool
is_same_set(struct set *s, int key1, int key2)
{
	assert(s != NULL);

	return (find(s, key1) == find(s, key2));
}

/*
 * Perform a join of two sets.
 */
void
set_union(struct set *s, int key1, int key2)
{
	int id1, id2;
	assert(s != NULL);
	
	id1 = find(s, key1);
	id2 = find(s, key2);

	if (id1 == id2) {
		// already in the same set
		return;
	}

	if (s->rank[id1] > s->rank[id2]) {
		s->parent[id2] = id1;
	} else {
		s->parent[id1] = id2;
		if (s->rank[id1] == s->rank[id2]) {
			s->rank[id2] += 1;
		}
	}
}

/*
 *  Create a set with the a single element.
 *   - with path compression
 */
void
make_set_pc(struct set *s, int key)
{
	assert(s != NULL);

	s->parent[key] = key;
	s->rank[key] = 0;
}

/*
 *  Find which set an element belongs to.
 *   - with path compression
 */
int
find_pc(struct set *s, int key)
{
	assert(s != NULL);

	if (key != s->parent[key]) {
		s->parent[key] = find(s, s->parent[key]);
	}
    return s->parent[key];
}

/*
 * Perform a join of two sets.
 *   - with path compression
 */
void
set_union_pc(struct set *s, int key1, int key2)
{
	assert(s != NULL);

	set_union(s, key1, key2);
}

int
main(int argc, char **argv)
{
	int size;
	struct set s;

	if (argc != 2) {
		printf("usage: ./sets <size of the set>\n");
		exit(-1);
	}

	size = atoi(argv[1]);

	// init the set
	set_init(&s, size);

	set_build(&s);

	set_dump(&s);

	// uinit a set
	set_uninit(&s);
}
