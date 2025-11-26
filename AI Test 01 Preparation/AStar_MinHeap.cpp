#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct Edge
{
	int to;
	int cost;
};

vector<vector<Edge>>graph;
vector<int>heuristic;

vector<int> AStar(int start, int goal)
{
    int n = graph.size();
    vector<int> g(n, INT_MAX);
    vector<int> parent(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    g[start] = 0;
    pq.push(make_pair(g[start] + heuristic[start], start));

    while (!pq.empty())
    {
        pair<int, int> top = pq.top();
        pq.pop();

        int f = top.first;
        int u = top.second;

        if (u == goal)
            break;
        for (size_t i = 0; i < graph[u].size(); i++)
        {
            int v = graph[u][i].to;
            int cost = graph[u][i].cost;

            if (g[u] + cost < g[v])
            {
                g[v] = g[u] + cost;
                parent[v] = u;
                pq.push(make_pair(g[v] + heuristic[v], v));
            }
        }
    }

    vector<int> path;
    int cur = goal;

    while (cur != -1)
    {
        path.push_back(cur);
        cur = parent[cur];
    }

    reverse(path.begin(), path.end());
    return path;
}
int main()
{
    int nodes, edges;
    cin >> nodes >> edges;

    graph.assign(nodes + 1, vector<Edge>());
    heuristic.assign(nodes + 1, 0);

    // read weighted edges
    for (int i = 0; i < edges; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({ v, w });
        graph[v].push_back({ u, w }); // undirected
    }

    // read heuristic values
    for (int i = 1; i <= nodes; i++)
        cin >> heuristic[i];

    int start, goal;
    cin >> start >> goal;

    vector<int> path = AStar(start, goal);

    cout << "A* Path: ";
    for (size_t i = 0; i < path.size(); i++)
        cout << path[i] << " ";
    cout << endl;

    return 0;
}
