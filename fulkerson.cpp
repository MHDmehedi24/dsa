#include <bits/stdc++.h>
using namespace std;

#define V 6  // Number of vertices in the graph

// BFS to find an augmenting path. Returns true if there is a path from source to sink.
bool bfs(vector<vector<int>>& rGraph, int s, int t, vector<int>& parent) {
    vector<bool> visited(V, false);
    queue<int> q;

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];
}

// Ford-Fulkerson algorithm
int fordFulkerson(vector<vector<int>>& graph, int s, int t) {
    vector<vector<int>> rGraph = graph;  // Residual graph
    vector<int> parent(V);  // Stores augmenting path
    int maxFlow = 0;

    // Augment the flow while there's a path from source to sink
    while (bfs(rGraph, s, t, parent)) {
        int pathFlow = INT_MAX;

        // Find the minimum capacity in the path filled by BFS
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        // Update residual capacities
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }

        // Add path flow to overall flow
        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    // Capacity matrix
    vector<vector<int>> graph = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
        
    };

    int source = 0, sink = 5;

    cout << "The maximum possible flow is " << fordFulkerson(graph, source, sink) << endl;

    return 0;
}
