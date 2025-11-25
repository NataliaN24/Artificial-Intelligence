Find the shortest path length from the start node to a given target using BFS

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;
vector<int>dist;

int bfs(int start, int target)
{
	queue<int>q;
	
	q.push(start);
	visited[start] = true;
	dist[start] = 0;
	while (!q.empty())
	{
		int top = q.front();
		q.pop();

		if (top == target)
		{
			return dist[top];
		}
		for (int v : graph[top])
		{
			if (!visited[v])
			{
				visited[v] = true;
				
				dist[v] = dist[top] + 1;
				q.push(v);
			}
		}
	}
	return -1;
}

int main()
{
	int nodes, edges;
	cin >> nodes >> edges;

	vector<pair<int, int>>edg;
	int maxNode = -1;

	for (int i = 0; i < edges; i++)
	{
		int u, v;
		cin >> u >> v;
		edg.push_back({ u,v });
		maxNode = max(maxNode, max(u, v));
	}
	graph.assign(maxNode + 1, {});
	visited.assign(maxNode + 1, false);
	dist.assign(maxNode + 1, -1);

	for (auto& p : edg)
	{
		graph[p.first].push_back(p.second);
		graph[p.second].push_back(p.first);
	}
	int start, target;
	cin >> start >> target;

	int ans = bfs(start, target);
	cout << ans << endl;
}
