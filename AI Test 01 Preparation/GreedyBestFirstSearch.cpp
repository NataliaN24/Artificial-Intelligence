#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

vector<vector<int>> graph;
vector<int> h;
vector<bool> visited;
vector<int> parent;

struct Node {
    int v, hv;
    bool operator<(const Node& other) const {
        return hv > other.hv;
    }
};

int greedyBestFirst(int start, int goal)
{
    priority_queue<Node> pq;
    pq.push({start, h[start]});
    visited[start] = true;
    parent[start] = -1;

    while (!pq.empty())
    {
        int u = pq.top().v;
        pq.pop();

        if (u == goal)
            return 1;

        for (int v : graph[u])
        {
            if (!visited[v])
            {
                visited[v] = true;
                parent[v] = u;
                pq.push({v, h[v]});
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
    visited.assign(n, false);
    parent.assign(n, -1);
    h.assign(n, 0);

    for (int i = 0; i < n; i++)
        cin >> h[i];

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int start, goal;
    cin >> start >> goal;

    if (greedyBestFirst(start, goal))
        printPath(goal);
    else
        cout << -1;
}
