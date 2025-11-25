Task Description

You are given an undirected graph with n nodes (labeled 0 → n–1) and m edges.
Your job is to use DFS to detect and count cycles in the graph.

A cycle means a path where you start at a node, follow edges, and return back to the same node without using an edge twice.

👉 You must find how many distinct cycles exist.

#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;

bool dfs(int node, int parent)
{
    visited[node] = true;

    for (int next : graph[node])
    {
        if (!visited[next])
        {
            if (dfs(next, node))
            {
                return true;
            }
        }
        else if (next != parent)
        {
            return true;
        }
     }
    return false;
}

int main()
{
    int edges;
    cin >> edges;

    vector<pair<int, int>> ed;
    int maxNode = -1;

    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        ed.push_back({ u,v });
        maxNode = max(maxNode, max(u, v));
    }

    graph.assign(maxNode + 1, {});
    visited.assign(maxNode + 1, false);

    for (auto& p : ed)
    {
        graph[p.first].push_back(p.second);
        graph[p.second].push_back(p.first);
    }

    int start;
    cin >> start;

    if (dfs(start, -1))
        cout << "cycle\n";
    else
        cout << "no cycle\n";
}
