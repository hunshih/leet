enum Visited_e {
    UNVISITED, TEMP_VISITED, VISITED
};

void topo_helper(const vector<vector<int>> &graph, vector<int> &order,
                 vector<Visited_e> &visited, int node){
    
    if (visited[node] == TEMP_VISITED){
        cout << "Cycle detected" << endl;
        return;
    }
    
    if (visited[node] == VISITED) return;
    
    visited[node] = TEMP_VISITED;
    for (int i = 0; i < graph[node].size(); ++i) {
        topo_helper(graph, order, visited, graph[node][i]);
    }
    visited[node] = VISITED;
    order.push_back(node);
    
}

vector<int> topo_sort(const vector<vector<int>> &graph){
    int n = (int)graph.size();
    vector<int> order;
    vector<Visited_e> visited(n, UNVISITED);
    
    for (int i = 0; i < n; ++i) {
        if (visited[i] == UNVISITED){
            topo_helper(graph, order, visited, i);
        }
    }
    return vector<int> (order.rbegin(), order.rend());
}