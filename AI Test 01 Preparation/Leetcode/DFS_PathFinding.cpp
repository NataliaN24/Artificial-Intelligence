You are given an undirected graph with n nodes and m edges.

Your task is to:

✔ Build the graph
✔ Perform Depth-First Search (DFS)
✔ Check whether there exists a path from start to goal
✔ If it exists, print the path (start → goal)
✔ If there is no path, print −1

Use a parent[] array to reconstruct the path.

  #include<iostream>
#include<vector>

using namespace std;

vector<vector<int>>graph;
vector<int>parent;
vector<bool>visited;

bool dfs(int start, int goal)
{
	visited[start] = true;

	if (start == goal)
	{
		return true;
	}
	for (int i : graph[start])
	{
		if (!visited[i])
		{
			parent[i] = start;
			if (dfs(i, goal)) {
				return true;
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
	parent[start] = -1;
	if (dfs(start, goal))
	{
		printPath(goal);
	}
	else
	{
		cout << -1;
	}
}
  
