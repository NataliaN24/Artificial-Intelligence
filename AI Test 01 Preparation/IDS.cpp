#include <iostream>
#include <vector>
using namespace std;

bool DLS(int node, int goal, int limit, vector<vector<int>>& graph, vector<int>& path) {
    path.push_back(node);

    if (node == goal)
        return true;

    if (limit == 0) {
        path.pop_back();
        return false;
    }

    for (int next : graph[node]) {
        if (DLS(next, goal, limit - 1, graph, path))
            return true;
    }

    path.pop_back();
    return false;
}

void IDS(int start, int goal, vector<vector<int>>& graph) {
    for (int depth = 0; depth < 1000; depth++) {
        vector<int> path;

        if (DLS(start, goal, depth, graph, path)) {
            cout << "Found at depth " << depth << "\n";
            cout << "Path: ";
            for (int p : path)
                cout << p << " ";
            cout << "\n";
            return;
        }
    }
    cout << "No path found.\n";
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

    int start, goal;
    cin >> start >> goal;

    IDS(start, goal, graph);
}
