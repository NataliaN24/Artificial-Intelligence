#include<iostream>
#include<vector>

using namespace std;


vector<vector<int>>graph;
vector<bool> visited;

void dfs(int start)
{
	visited[start] = true;
	cout << start << " ";

	for (int v : graph[start])
	{
		if (!visited[v])
		{
			dfs(v);
		}
	}
}

int main()
{
	int nodes;
	int edges;
	cin >> nodes;
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

	for (auto& p : edg)
	{
		graph[p.first].push_back(p.second);
		graph[p.second].push_back(p.first);
	}
	int start;
	cin >> start;
	cout << "DFS order:" << '\n';

	dfs(start);
	cout << endl;
}



