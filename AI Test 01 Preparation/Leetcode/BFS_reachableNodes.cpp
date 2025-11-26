Count how many nodes are reachable from the start node
Description

Using BFS, count how many nodes you can reach starting from a given node.

This includes the start node itself.


#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;

int bfs(int start)
{
    queue<int> q;
    q.push(start);
    visited[start] = true;
    int nodes=1;

    while (!q.empty())
    {      
       int u = q.front();
        q.pop();

            for (int v : graph[u])
            {
                if (!visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                    nodes++;
                }
            }
    }

    return nodes;
}

int main()
{
    int nodes, edges;
    cin >> nodes >> edges;

    graph.assign(nodes, {});
    visited.assign(nodes, false);

    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int start;
    cin >> start;

    cout << bfs(start);
}
