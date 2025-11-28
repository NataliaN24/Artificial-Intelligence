#include<iostream>
#include<vector>
#include<queue>
#include <cmath>
#include <algorithm>
#include<set>
using namespace std;


vector<vector<pair<int,int>>>graph;
vector<bool>visited;
vector<int>parent;
vector<int>h;
vector<int>g;

struct Node
{
	int v;
	int f;
	bool operator<(const Node& other)const
	{
		return f > other.f;

	}
};

bool Astar(int start, int goal)
{
	priority_queue<Node>pq;
	g[start] = 0;
	parent[start] = -1;
	pq.push({ start,h[start]+g[start]});

	while (!pq.empty())
	{
		int node = pq.top().v;
		pq.pop();

		if (visited[node])continue;

		visited[node] = true;

		if (node == goal)return true;

		for (auto& pr : graph[node])
		{
			int v = pr.first;
			int cost = pr.second;
			int newG = g[node] + cost;

			if (newG < g[v])
			{
				g[v] = newG;
				parent[v] = node;
				pq.push({ v,g[v] + h[v] });
			}
		}
	}
	return false;
}

void printPath(int target)
{
	vector<int>path;
	int u = target;
	while (u != -1)
	{
		path.push_back(u);
		u = parent[u];
	}
	reverse(path.begin(), path.end());
	for (int c : path)
	{
		cout << c << " ";
	}
}


int main()
{
	int n, edges;
	cin >> n >> edges;

	graph.assign(n, {});
	h.assign(n, 0);
	g.assign(n, 1000000000);
	parent.assign(n, -1);
	visited.assign(n, false);

	for (int i = 0; i < n; i++)
	{
		cin >> h[i];
	}
	for (int i = 0; i < edges; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		graph[u].push_back({ v,w });
		graph[v].push_back({ u,w });
	}
	int start, goal;
	cin >> start >> goal;

	if (Astar(start, goal))
		printPath(goal);
	else
		cout << -1;
}
