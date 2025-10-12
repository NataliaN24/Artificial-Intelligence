#include <iostream>
#include <vector>

using namespace std;

// ------------------------------
// GRAPH CLASS (your version)
// ------------------------------

class Graph {
    int numVertices;
    vector<int>* adjList;
    bool directed;

public:
    Graph(int V, bool directed);
    void addEdge(int v, int w);
    vector<int> adj(int v);
    int vertices() const;
    ~Graph();
};

Graph::Graph(int V, bool directed) {
    numVertices = V;
    adjList = new vector<int>[V];
    this->directed = directed;
}

void Graph::addEdge(int v, int w) {
    adjList[v].push_back(w);
    if (!directed) {
        adjList[w].push_back(v);
    }
}

vector<int> Graph::adj(int v) {
    return adjList[v];
}

int Graph::vertices() const {
    return numVertices;
}

Graph::~Graph() {
    delete[] adjList;
}

// ------------------------------
// DEPTH-LIMITED SEARCH (DLS)
// ------------------------------

bool DLS(Graph& g,int v, int goal, int limit, vector<bool>& visited)
{
    cout << "Visiting node " << v << ", depth limit = " << limit << endl;
    if (v == goal)
    {
        cout << "Goal " << goal << " found!" << endl;
        return true;
    }
    if (limit <= 0)
    {
        return false;
    }
    visited[v] = true;
    for (int neighbor : g.adj(v))
    {
        if (!visited[neighbor])
        {
            if (DLS(g, neighbor, goal, limit - 1, visited))
            {
                return true;
            }
        }
        return false;
    }
}

int main() {
    Graph g(7, false); // undirected graph

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    int start = 0;
    int goal = 5;
    int limit = 2; // maximum depth

    vector<bool> visited(g.vertices(), false);

    cout << "Depth-Limited Search from " << start
        << " to " << goal << " with limit " << limit << ":\n";

    bool found = DLS(g, start, goal, limit, visited);

    if (!found)
        cout << "Goal not found within depth limit " << limit << endl;

    return 0;
}
