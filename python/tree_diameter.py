#!/usr/bin/python
'''
Problem Statement:
You got sick because of walking in the woods at night, and have to spend a week at home without going out. Looking out of the window at the nearby woods you're wondering if there is anything you don't yet know about them. Suddenly you see a beautiful and very tall tree you haven't seen before. Since you have nothing to do, you decide to examine its structure and draw it in your notebook.

You became so exited about this new tree that your temperature went up, so you were forced to stay in bed. You can't see the tree from your bed, but luckily you have it drawn down. The first thing you'd like to find out about is the tree height. Looking at your drawing you suddenly realize that you forgot to mark the tree bottom and you don't know from which vertex you should start counting. Of course a tree height can be calculated as the length of the longest path in it (it is also called tree diameter). So, now you have a task you need to solve, so go ahead!

Example

For n = 10 and

tree = [[2, 5], [5, 7], [5, 1], [1, 9], [1, 0], [7, 6], [6, 3], [3, 8], [8, 4]]
the output should be treeDiameter(n, tree) = 7.



The longest path is the path from vertex 4 to one vertex 9 or 0.

Input/Output

[execution time limit] 4 seconds (py3)

[input] integer n

The number of vertices in the structure you drew in your notebook.

Guaranteed constraints:
1 ≤ n ≤ 104.

[input] array.array.integer tree

Edges of the tree. tree[i] for each valid i contains two elements and represents an edge that connects tree[i][0] and tree[i][1].
It is guaranteed that given graph is a tree, i.e. it is connected and has no cycles.

Guaranteed constraints:
tree.length = n - 1,
tree[i].length = 2,
0 ≤ tree[i][j] < n.

[output] integer

tree diameter of the given tree.
=========================================================

Solution:
    1. Traverse the array which represents the tree.
    2. Build an adjacency list representation of the tree (which is truely a graph).
    3. Perform a BFS from the starting node in the graph/tree.
    4. BFS in step 3 will terminate at the node furthest from the root node.
    5. Now, perform a BFS starting from the node furthest from the root node 'Node X'.
    6. BFS in step 5 will terminate at the node furthest from 'Node X'
    7. This will give us the length of the longest path in the tree (graph).
'''
def visited(s, ele):
    return ele in s

def visit(s, ele):
    s.add(ele)
    
def bfs(graph, start):
    v_map = set()
    q = []
    
    q.insert(0, start)
    visit(v_map, start)
    level = -1
    #last_element = -1
    
    while len(q) > 0:
        level += 1
        #print("[%d]" % (level))
        size = len(q)
        
        while size > 0:
            ele = q.pop()
            #print("Processing: %d" % (ele))
            #last_element = ele
            ns = graph[ele]
            for n in ns:
                if not visited(v_map, n):
                    visit(v_map, n)
                    q.insert(0, n)
                    
            size = size - 1
    
    #print("Last Element: %d" % (ele))
    #print("Level: %d" % (level))
    return ele, level

def treeDiameter(n, tree):
    if n is 0 or len(tree) is 0:
        return 0
    
    table = dict()
    
    for i in range(n):
        table[i] = []
        
    # build the graph
    # build an adjacency list representation of a graph
    # using a dictionary, indexed by vertex.
    for i in range(len(tree)):
        e1 = tree[i][0]
        e2 = tree[i][1]
        
        l1 = table[e1]
        l2 = table[e2]
        
        l1.append(e2)
        l2.append(e1)
        
    #print(table)
    
    starting_node = tree[0][0]
    
    # performa a Breath First Search.
    # this will terminate at the node furtherst from the root node.
    # also get the distance from the root node.
    ending_node, length = bfs(table, starting_node)
    #print(ending_node)
    
    # Now perform another BFS keeping the last node (from the previous BFS) as
    # the starting node.
    # this will terminate at the node which is furthest from 'this new starting node', 
    # given the length of the longest path from this node.
    last_node, result = bfs(table, ending_node)
    #print(result)
    return result
        

