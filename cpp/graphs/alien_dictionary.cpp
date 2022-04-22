

void dfs(char node,
         unordered_map<char, int> &visited,
         unordered_map<char, int> &arrival,
         unordered_map<char, int> &departure,
         int &timestamp,
         string &toposort,
         unordered_map<char, unordered_set<char>> &adj_map) {
    visited[node] = 1;
    arrival[node] = timestamp++;
    
    char neigh;
    for (auto it = adj_map[node].begin(); it != adj_map[node].end(); it++) {
        neigh = *it;
        if (visited[neigh] == 0) {
            dfs(neigh, visited, arrival, departure, timestamp, toposort, adj_map);
        }
    }
    
    departure[node] = timestamp++;
    toposort.push_back(node);
}

string find_order(vector<string> &words) {
    // Write your code here.
    if (words.size() == 1) {
        return {words[0][0]};
    }
    
    unordered_map<char, unordered_set<char>> adj_map;
    
    unordered_set<char> letters;
    
    string first;
    string second;
    int i;
    int j;
    char src;
    char dst;
    bool found = false;
    for (int idx = 1; idx < words.size(); idx++) {
        first = words[idx-1];
        second = words[idx];
        
        i = 0;
        j = 0;
        found = false;
        while (i < first.size() && j < second.size()) {
            letters.insert(first[i]);
            letters.insert(second[j]);
            if (first[i] != second[j]) {
                src = first[i];
                dst = second[j];
                found = true;
                break;
            }
            i++;
            j++;
        }
        
        if (found) {
            //letters.insert(dst);
            //letters.insert(src);
            printf("(%c) -> (%c)\n", src, dst);
            
            adj_map[src].insert(dst);
        }
    }
    printf("letter count : %d\n", (int)letters.size());
    
    if (letters.size() == 1) {
        auto it = letters.begin();
        return {*it};
    }
    unordered_map<char, int> visited;
    unordered_map<char, int> arrival;
    unordered_map<char, int> departure;
    
    for (auto it = letters.begin(); it != letters.end(); it++) {
        visited.insert({*it, 0});
        arrival.insert({*it, -1});
        departure.insert({*it, -1});
    }
    
    int timestamp = 0;
    string toposort;
    
    for (auto it = letters.begin(); it != letters.end(); it++) {
        if (visited[*it] == 0) {
            dfs(*it, visited, arrival, departure, timestamp, toposort, adj_map);
        }
    }
    
    reverse(toposort.begin(), toposort.end());
    
    return toposort;
}

