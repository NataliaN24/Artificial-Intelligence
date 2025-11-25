#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct Edge {
    int to;
    int cost;
};

vector<int> uniformCostSearch(vector<vector<Edge>>& graph, int start, int goal) {
    int n = graph.size();

    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int cost = top.first;
        int u = top.second;

        if (visited[u]) continue;
        visited[u] = true;

        if (u == goal) break;

        for (auto& e : graph[u]) {
            int v = e.to;
            int w = e.cost;

            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    vector<int> path;
    if (dist[goal] == INT_MAX) return path;

    for (int cur = goal; cur != -1; cur = parent[cur])
        path.push_back(cur);

    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int nodes, edges;
    cin >> nodes >> edges;

    vector<vector<Edge>> graph(nodes);

    for (int i = 0; i < edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int start, goal;
    cin >> start >> goal;

    vector<int> path = uniformCostSearch(graph, start, goal);

    if (path.empty()) {
        cout << "No path\n";
    } else {
        cout << "UCS Path: ";
        for (int x : path) cout << x << " ";
        cout << "\n";
    }

    return 0;
}
