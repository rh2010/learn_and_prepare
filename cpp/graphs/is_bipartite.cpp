/*
 * DFS Solution
    - yes, we need to transform the input to an adjacemcy-list
    
    - yes, we need an outer loop
    - dfs
    
    - color the nodes alternatively.
*/
class Solution {
    bool canBeBipartite(int node, vector<int> &parent, vector<int> &visited, vector<int> &color, vector<vector<int>> &adj_list, int c) {
        visited[node] = 1;
        
        for (int v = 0; v < adj_list[node].size(); v++) {
            int neigh = adj_list[node][v];
            //printf("\t p (%d) n (%d), visited[neigh] (%d)\n", node, neigh, visited[neigh]);
            if (!visited[neigh]) {
                parent[neigh] = v;
                //printf("color[%d] = %d]", neigh, 1-c);
                color[neigh] = 1-c;
                if (!canBeBipartite(neigh, parent, visited, color, adj_list, 1-c)) {
                    return false;
                }
            } else {// already visited
                // if the color is same, the Bipartition cannot be formed.
                if (color[neigh] == color[node]) {
                    //printf("Color of neighbor (%d) and parent (%d) is same (%d)", neigh, node, color[node]);
                    return false;
                }
            }
        }
        return true;
    }
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        vector<int> visited(n, 0);
        vector<int> color(n, -1);
        vector<int> parent(n, -1);
        
        vector<vector<int>> adj_list(n);
        
        // transform
        for (int i = 0; i<dislikes.size(); i++) {
            int src = dislikes[i][0]-1;    
            int dst = dislikes[i][1]-1;
            
            adj_list[src].push_back(dst);
            adj_list[dst].push_back(src);
        }
        
        for (int v = 0; v < n; v++) {
            if (!visited[v]) {
                //printf("String dfs from (%d), color %d\n", v, 0);
                color[v] = 0; // start with color '0'
                if (!canBeBipartite(v, parent, visited, color, adj_list, 0)) {
                    return false;
                }
            }
            
        }
        return true;
    }
};

/*
 * 	BFS Solution
    - this is given as a graph problem
    - need to re-represent the graph (NO)
        - the input is an adjacency list already.
    - Do we need an outer loop (YES)
        - we need to check all the vertices in the graph
    - bfs or dfs -> BFS
    - extend basic bfs. YES

Notes:-
    - split the vertices in 2 teams.
    - every pair of vertices on an edge should be is different teams.
    - there should be no edge internal to a team / group.
    - For checking if a graph is barpitite - each component has to be checked independently
      if there are more than one component. Therefore, we need an outer loop.
    - cycles of ODD length means graph is not bipartite
    - if there are no cycles then the graph is Bipartite
    - Even cycles are ok, i.e. graph is still bipartite.
    
*/
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        
        // visited - initialized to 0
        vector<int> visited(n, 0);
        
        // parent - initialized to -1
        vector<int> parent(n, -1);
        
        // distance - initialize to -1
        vector<int> distance(n, -1);
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (!bfs(i, visited, parent, distance, graph)) {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool bfs(int source, vector<int> &visited, vector<int> &parent, vector<int> &distance, vector<vector<int>> &graph) {
        distance[source] = 0;
        visited[source] = 1;
        
        // we don't set the parent for the source node.
        
        queue<int> q;
        q.push(source);
        
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            
            // loop over neighbors
            for (int i = 0; i < graph[curr].size(); i++) {
                int neighbor = graph[curr][i];
                if (!visited[neighbor]) { // neighbor not visited yet.
                    visited[neighbor] = 1;
                    parent[neighbor] = curr;
                    distance[neighbor] = 1 + distance[curr];
                    q.push(neighbor);
                } else { // neighbor is already visited
                    if (parent[curr] == neighbor) { // neighbor is the parent
                        continue;
                    } else {
                        // if the parent of curr is not the neighbor, then,
                        // this is a cross-edge / back-edge
                        // CYCLE DETECTED!
                        
                        // check is the cycle is even or odd
                        // to check this:
                        //  - if the distance of the curr and neighbor is same
                        //    then this is an odd cycle.
                        //  - if the distance of curr and distance of neighbor are different than than means
                        //  - this is an even cycle (this is true only for un-directed graphs.)
                        //  - 
                        if (distance[curr] == distance[neighbor]) {
                            return false;
                        }
                    }
                }
            } // for
        } // while
        return true;
    } // bfs
};
