DFS Task: Count How Many Nodes Are Reachable From a Given Start Node
Problem Statement

You are given:

A graph with n nodes (numbered arbitrarily)

A list of edges

A starting node s

Your task:
Use DFS to count how many nodes can be reached starting from s.

What does “reachable” mean?

A node is reachable from s if there is a path from s to that node.

  #include<iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

vector<vector<int>>graph;
vector<bool>visited;

int dfs(int node)
{
	visited[node] = true;
	int count = 1;
	for (int x : graph[node])
	{
		if (!visited[x])
		{
			dfs(x);
			count++;
		}
	}
	return count;
}

int main()
{
	int edges;
	cin >> edges;
	vector<pair<int, int>>edg;
	int maxNode = -1;

	for (int i = 0; i < edges; i++)
	{
		int u, v;
		cin >> u >> v;
		edg.push_back({ u,v });
		maxNode = max(maxNode, max(u, v));
	}

	graph.assign(maxNode+1,{});
	visited.assign(maxNode + 1, false);
	for (auto& i : edg)
	{
		graph[i.first].push_back(i.second);
		graph[i.second].push_back(i.first);
	}
	int node;
	cin >> node;
	
	cout << dfs(node) << endl;
}
