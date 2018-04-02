#include "../util.h"
#include <time.h>

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

// set interfaces
//
// interfaces for approach a)
void make_set(int key);
int find(int key);
void set_union(int key1, int key2);

// interfaces for approach b)
void make_set_pc(int key);
int find_pc(int key);
void set_union_pc(int key1, int key2);

/*
 *
 *  make_set - Create a set with the a single element.
 */
void
make_set(int key)
{

}

/*
 *  Find which set an element belongs to.
 */
int
find(int key)
{
    return 0;
}

/*
 * Perform a join of two sets.
 */
void
set_union(int key1, int key2)
{

}

/*
 *  Create a set with the a single element.
 *   - with path compression
 */
void
make_set_pc(int key)
{

}

/*
 *  Find which set an element belongs to.
 *   - with path compression
 */
int
find_pc(int key)
{
    return 0;
}

/*
 * Perform a join of two sets.
 *   - with path compression
 */
void
set_union_pc(int key1, int key2)
{

}
