#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<vector<int>> graph;
vector<int> h; // heuristic
vector<int> parent;

struct Node {
    int v;
    int hv;
};

// Sort by heuristic
bool cmp(const Node& a, const Node& b) {
    return a.hv < b.hv;
}

bool beamSearch(int start, int goal, int K)
{
    parent.assign(graph.size(), -1);

    vector<int> beam; 
    beam.push_back(start);

    while (!beam.empty())
    {
        vector<Node> successors;

        // Expand ALL nodes in the current beam
        for (int u : beam)
        {
            if (u == goal) return true;

            for (int v : graph[u])
            {
                successors.push_back({ v, h[v] });
                parent[v] = u;
            }
        }

        if (successors.empty())
            return false;

        // Keep only the best K by heuristic
        sort(successors.begin(), successors.end(), cmp);

        beam.clear();
        for (int i = 0; i < successors.size() && i < K; i++)
            beam.push_back(successors[i].v);
    }

    return false;
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

    int K; // beam width
    cin >> K;

    if (beamSearch(start, goal, K))
        printPath(goal);
    else
        cout << -1;
}
