#include <iostream>
#include <vector>
using namespace std;

void DLS(int node, int goal, int limit,
         vector<vector<int>>& graph,
         vector<bool>& visited,
         vector<int>& path,
         bool& found)
{
    if (found) return;

    visited[node] = true;
    path.push_back(node);

    if (node == goal) {
        found = true;
        cout << "Path found: ";
        for (int x : path) cout << x << " ";
        cout << "\n";
        return;
    }

    if (limit == 0) {
        path.pop_back();
        return;
    }

    for (int next : graph[node]) {
        if (!visited[next]) {
            DLS(next, goal, limit - 1, graph, visited, path, found);
            if (found) return;
        }
    }

    path.pop_back();
}

int main() {
    int n, e;
    cin >> n >> e;

    vector<vector<int>> graph(n);

    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int start, goal, limit;
    cin >> start >> goal >> limit;

    vector<bool> visited(n, false);
    vector<int> path;
    bool found = false;

    DLS(start, goal, limit, graph, visited, path, found);

    if (!found) {
        cout << "No path found within depth limit.\n";
    }

    return 0;
}
