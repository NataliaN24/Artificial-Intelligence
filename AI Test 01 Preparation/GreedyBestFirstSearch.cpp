#include<iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct Edge
{
	int to;
	int cost;
};

vector<int> greedy(vector<vector<Edge>>& graph, vector<int>& heuristic, int start, int goal)
{
	int n = graph.size();
	vector<bool>visited(n, false);
	vector<int>parent(n, -1);//to construct the path
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>pq;
	
	pq.push(make_pair(heuristic[start], start));

	while (!pq.empty())
	{
		auto top = pq.top();
		pq.pop();
		int hVal = top.first;
		int u = top.second;

		
		if (visited[u]) continue;
		visited[u] = true;

		if (u == goal)
		{
			vector<int>path;
			int cur = goal;
			while (cur != -1)
			{
				path.push_back(cur);
				cur = parent[cur];
			}
			reverse(path.begin(), path.end());
			return path;
		}
		for (auto& e : graph[u])
		{
			int v = e.to;
			if (!visited[v])
			{
				parent[v] = u;
				pq.push(make_pair(heuristic[v], v));
			}
		}
	}
	return {};
}


int main()
{
	int nodes, edges;
	cin >> nodes >> edges;

	vector<vector<Edge>>graph(nodes);
	vector<int> h(nodes);

	for (int i = 0;i<edges;i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		graph[u].push_back({ v,w });
		graph[v].push_back({ u,w });
	}

	for (int i = 0; i < nodes; i++)
	{
		cin >> h[i];
	}
	int start, goal;
	cin >> start >> goal;
	vector<int> path = greedy(graph, h, start, goal);

	if (path.empty())
	{
		cout << "No path\n";
	}
	else
	{
		cout << "Path exists\nPath: ";
		for (int x : path) cout << x << " ";
		cout << endl;
	}

	return 0;
}
