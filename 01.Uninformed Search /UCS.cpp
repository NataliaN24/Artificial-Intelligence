//1st option

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

using namespace std;


class Graph {
    int numVertices;
    vector<vector<pair<int, int>>> adjList; // pair<neighbor, cost>
    bool directed;

public:
    Graph(int V, bool directed)
        : numVertices(V), adjList(V), directed(directed) {
    }

    void addEdge(int v, int w, int cost) {
        adjList[v].push_back({ w, cost });
        if (!directed) {
            adjList[w].push_back({ v, cost });
        }
    }

    vector<pair<int, int>> adj(int v) const {
        return adjList[v];
    }

    int vertices() const {
        return numVertices;
    }
};

// ------------------------------
// UNIFORM-COST SEARCH (UCS)
// ------------------------------

void uniformCostSearch(const Graph& g, int start, int goal) {
    // Initialize costs to "infinity"
    vector<int> cost(g.vertices(), numeric_limits<int>::max());

    // Priority queue for UCS: pair<cost, vertex>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    cost[start] = 0;
    pq.push({ 0, start });

    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        int currentCost = top.first;
        int v = top.second;
        pq.pop();

        // Goal check
        if (v == goal) {
            cout << "Reached goal " << goal << " with total cost: " << currentCost << endl;
            return;
        }

        // Skip if a better path to v is already found
        if (currentCost > cost[v])
            continue;

        // Explore neighbors
        for (auto neighborPair : g.adj(v)) {
            int neighbor = neighborPair.first;
            int edgeCost = neighborPair.second;
            int newCost = currentCost + edgeCost;

            if (newCost < cost[neighbor]) {
                cost[neighbor] = newCost;
                pq.push({ newCost, neighbor });
            }
        }
    }

    cout << "Goal not reachable from start node." << endl;
}


int main() {
  
    Graph g(6, false);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 3);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, 5);

    int start = 0;
    int goal = 5;

    cout << "Uniform-Cost Search from " << start << " to " << goal << ":\n";
    uniformCostSearch(g, start, goal);

    return 0;
}

//2nd option
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    int to;
    int cost;
};

vector<vector<Edge>> graph = {
    { {1, 2}, {2, 5} },     // 0 -> 1 (2), 0 -> 2 (5)
    { {3, 1} },             // 1 -> 3 (1)
    { {3, 2} },             // 2 -> 3 (2)
    {}                      // 3
};

struct Node {
    int id;
    int g; // cost so far
};

struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.g > b.g;   // min-heap (smallest g on top)
    }
};

int UCS(int start, int goal) {
    priority_queue<Node, vector<Node>, Compare> pq;
    vector<int> dist(4, 1e9);

    dist[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        Node u = pq.top();
        pq.pop();

        if (u.id == goal)
            return u.g;

        for (auto& e : graph[u.id]) {
            int v = e.to;
            int w = e.cost;

            if (u.g + w < dist[v]) {
                dist[v] = u.g + w;
                pq.push({v, dist[v]});
            }
        }
    }

    return -1;
}

int main() {
    cout << "Cost: " << UCS(0, 3);
    return 0;
}

