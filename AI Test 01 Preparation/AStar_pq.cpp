#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

vector<vector<pair<int,int>>> graph;
vector<int> h;
vector<int> g;
vector<int> parent;
vector<bool> visited;

struct Node {
    int v, f;
    bool operator<(const Node& other) const {
        return f > other.f;
    }
};

int astar(int start, int goal)
{
    priority_queue<Node> pq;
    pq.push({start, h[start]});
    g[start] = 0;
    parent[start] = -1;

    while (!pq.empty())
    {
        int u = pq.top().v;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        if (u == goal) return 1;

        for (auto& p : graph[u])
        {
            int v = p.first;
            int cost = p.second;

            int new_g = g[u] + cost;

            if (new_g < g[v])
            {
                g[v] = new_g;
                parent[v] = u;
                pq.push({v, g[v] + h[v]});
            }
        }
    }

    return 0;
}

void printPath(int goal)
{
    vector<int> path;
    int u = goal;
    while (u != -1)
    {
        path.push_back(u);
        u = parent[u];
    }
    reverse(path.begin(), path.end());
    for (int x : path) cout << x << " ";
}

int main()
{
    int n, m;
    cin >> n >> m;

    graph.assign(n, {});
    h.assign(n, 0);
    g.assign(n, 1e9);
    parent.assign(n, -1);
    visited.assign(n, false);

    for (int i = 0; i < n; i++)
        cin >> h[i];

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int start, goal;
    cin >> start >> goal;

    if (astar(start, goal))
        printPath(goal);
    else
        cout << -1;
}
