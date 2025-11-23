#include<iostream>
#include<vector>
#include< queue>

using namespace std;

vector<vector<int>>graph;
vector<bool>visited;

void bfs(int start)
{
	queue<int>q;
	q.push(start);
	visited[start] = true;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		cout << u << " ";
		for (int v : graph[u])
		{
			if (!visited[v])
			{
				visited[v] = true;
				q.push(v);
			}
		}

	}
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
	for (auto& p : edg)
	{
		graph[p.first].push_back(p.second);
		graph[p.second].push_back(p.first);
	}
	int start;
	cin >> start;
	cout << "BFS order" << " ";
	bfs(start);
	cout << endl;
}
