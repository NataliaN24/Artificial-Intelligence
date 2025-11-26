Count how many nodes are at exact distance K from the start node using BFS
Output

Print the number of nodes that are exactly K edges away from the start node.

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;

int bfs(int start, int k)
{
    queue<int> q;
    q.push(start);
    visited[start] = true;
    int dist = 0;

    while (!q.empty())
    {
        int sz = q.size();
        if (dist == k)
            return sz;

        while (sz--)
        {
            int u = q.front();
            q.pop();

            for (int v : graph[u])
            {
                if (!visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        dist++;
    }

    return 0;
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

    int start, k;
    cin >> start >> k;

    cout << bfs(start, k);
}
