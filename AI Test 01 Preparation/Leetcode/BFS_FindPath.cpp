You are given an unweighted, undirected graph with n nodes and m edges.

Your task is to:

✔ Build the graph
✔ Perform Breadth-First Search (BFS) starting from node start
✔ Find the shortest path to node goal
✔ Print the shortest path
✔ If no path exists → print -1

This requires using a queue, a parent[] array, and a visited[] array.

#include<iostream>
#include<vector>
#include<queue>
#include <algorithm>


using namespace std;

vector<vector<int>>graph;
vector<bool>visited;
vector<int>parent;

bool bfs(int start, int goal)
{
	queue<int>q;

	q.push(start);
	visited[start] = true;
	parent[start] = -1;

	while (!q.empty())
	{
		int el = q.front();
		q.pop();
		if (el == goal)
		{
			return true;
		}

		for (int v : graph[el])
		{
			if (!visited[v])
			{
				visited[v] = true;
				parent[v] = el;
				q.push(v);
			}
		}
	}
	return false;
}

void printPath(int goal)
{
	int u = goal;
	vector<int>path;
	while (u != -1)
	{
		path.push_back(u);
		u = parent[u];
	}
	reverse(path.begin(), path.end());
	for (int x : path)
	{
		cout << x << " ";
	}

}

int main()
{
	int n, m;
	cin >> n >> m;
	graph.assign(n, {});
	parent.assign(n, -1);
	visited.assign(n, false);
	for (int i = 0; i < m; i++)
	{
		int v, u;
		cin >> v >> u;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}
	int start, goal;
	cin >> start >> goal;
	
	if (bfs(start, goal))
	{
		printPath(goal);
	}
	else
	{
		cout << -1;
	}
}
