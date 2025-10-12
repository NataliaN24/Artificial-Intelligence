#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Graph
{
    int numVertices;
    vector<int>* adjList;
    bool directed;

public:
	Graph(int V,bool directed);
	void addEdge(int v, int w);
	vector<int>adj(int v);
	int vertices()const ;
    ~Graph();
};

Graph::Graph(int V, bool directed)
{
    numVertices = V;
    adjList = new vector<int>[V];
    this->directed = directed;

}

void Graph::addEdge(int v, int w)
{
    adjList[v].push_back(w);
    if (!directed)
    {
        adjList[w].push_back(v);
    }
}

vector<int> Graph::adj(int v)
{
    return adjList[v];
}

int Graph::vertices()const
{
    return numVertices;
}

Graph::~Graph()
{
    delete[]adjList;
}

class DFS_recursive
{
    bool* visited;
    Graph &g;
public:
    DFS_recursive(Graph& g);
    void dfs(int v);
    ~DFS_recursive();

};
DFS_recursive::DFS_recursive(Graph& g):g(g),visited(new bool[g.vertices()])
{
    fill(visited, visited + g.vertices(), false);
}

void DFS_recursive::dfs(int v)
{
    visited[v] = true;
    cout << v << " ";
    for (int w : g.adj(v)) {
        if (!visited[w]) {
            dfs(w);
        }
    }
}

DFS_recursive::~DFS_recursive()
{
    delete[]visited;
}


int main() {
    Graph g(5, false); 

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    DFS_recursive dfsTraversal(g);
    cout << "Recursive DFS starting from vertex 0:" << endl;
    dfsTraversal.dfs(0);
    cout << endl;

    return 0;
}
