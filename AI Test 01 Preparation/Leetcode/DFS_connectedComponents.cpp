Task: Count how many connected components the graph has.

A connected component is a group of nodes where each node can reach every other node using edges.

  #include<iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

vector<vector<int>>graph;
vector<bool>visited;

void dfs(int node)
{
	visited[node] = true;
	for (int x : graph[node])
	{
		if (!visited[x])
		{
			dfs(x);
		}
	}
}

int main()
{
	int edges;
	cin >> edges;
	vector<pair<int, int>>edg;
	int maxNode = -1;
	vector<int> nodesAppearing;

	for (int i = 0; i < edges; i++)
	{
		int u, v;
		cin >> u >> v;
		edg.push_back({ u,v });
		maxNode = max(maxNode, max(u, v));
		nodesAppearing.push_back(u);
		nodesAppearing.push_back(v);

	}
	graph.assign(maxNode+1,{});
	visited.assign(maxNode + 1, false);
	for (auto& i : edg)
	{
		graph[i.first].push_back(i.second);
		graph[i.second].push_back(i.first);
	}
	int connectedComponents = 0;
	for (int node : nodesAppearing)
	{
		if (!visited[node])
		{
			dfs(node);
			connectedComponents++;
		}
	}
	cout << connectedComponents << endl;
}
