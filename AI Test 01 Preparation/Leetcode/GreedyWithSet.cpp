#include<iostream>
#include<vector>
#include<queue>
#include <cmath>
#include <algorithm>
#include<set>
using namespace std;

vector<vector<int>>graph;
vector<int>parent;
vector<bool>visited;
vector<int>h;

struct Node
{
	int v;
	int hv;
	bool operator<(const Node& other)const
	{
		return hv > other.hv;
	}
};
bool greedyBSF(int startNode, int target)
{
	priority_queue<Node>pq;
	pq.push({ startNode,h[startNode] });
	visited[startNode] = true;
	parent[startNode] = -1;

	while (!pq.empty())
	{
		int topEl = pq.top().v;
		pq.pop();

		if (topEl == target)
		{
			return true;
		}
		for (int succ : graph[topEl])
		{
			if (!visited[succ])
			{
				visited[succ] = true;
				parent[succ] = topEl;
				pq.push({ succ,h[succ] });


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
	for (int x : path)
	{
		cout << x << " ";
	}
}


int main()
{
	int nodes;
	int edges;
	cin >> nodes >> edges;
	
	int maxNode = -1;
	vector<pair<int, int>>p;
	for (int i = 0; i < edges; i++)
	{
		int u, v;
		cin >> u >> v;
		p.push_back({ u,v });
		maxNode = max(maxNode, max(u, v));
	}

	graph.assign(maxNode + 1, {});
	parent.assign(maxNode + 1, -1);
	visited.assign(maxNode + 1, false);
	h.assign(maxNode + 1, 0);

	set<int>existingNodes;
	for (auto& pr : p)
	{
		existingNodes.insert(pr.first);
		existingNodes.insert(pr.second);
	}
	for (int i :existingNodes)
	{
		cin >> h[i];
	}
	for (auto& el : p)
	{
		graph[el.first].push_back(el.second);
		graph[el.second].push_back(el.first);
	}
	int start, target;
	cin >> start >> target;
	if (greedyBSF(start, target))
	{
		printPath(target);
	}
	else {
		cout << -1;
	}

}
