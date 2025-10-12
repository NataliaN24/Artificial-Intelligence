#include <iostream>
#include <vector>
#include <queue>
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

class BFS_iterative
{
    bool* visited;
    Graph &g;
public:
    BFS_iterative(Graph& g);
    void bfs(int v);
    ~BFS_iterative();

};
BFS_iterative::BFS_iterative(Graph& g):g(g),visited(new bool[g.vertices()])
{
    fill(visited, visited + g.vertices(), false);
}

void BFS_iterative::bfs(int v)
{
    queue<int>notVisited;
    notVisited.push(v);
    visited[v] = true;
    while (!notVisited.empty()) {
        v = notVisited.front();
        notVisited.pop();
        cout << v << " ";
        for (int w : g.adj(v)) {
            if (!visited[w]) {
                visited[w] = true;
                notVisited.push(w);
            }
        }
    }

    
}

BFS_iterative::~BFS_iterative()
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

    BFS_iterative bfsTraversal(g); 
    cout << "Iterative BFS starting from vertex 0:" << endl;
    bfsTraversal.bfs(0); 
    cout << endl;

    return 0;
}
