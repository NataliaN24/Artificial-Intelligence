#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
    int to;
    int cost;
};

vector<vector<Edge>> graph = {
    { {1, 2}, {2, 5} },  // 0 -> 1 (2), 0 -> 2 (5)
    { {3, 1} },          // 1 -> 3 (1)
    { {3, 2} },          // 2 -> 3 (2)
    {}                   // 3
};

// Примерна евристика h(n)
int h(int node) {
    int heuristics[] = {4, 2, 3, 0};
    return heuristics[node];
}

struct Node {
    int id;
    int g; // реална цена
    int f; // g + h
};

struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.f > b.f;   // мин-heap
    }
};

int Astar(int start, int goal) {
    priority_queue<Node, vector<Node>, Compare> pq;
    vector<int> dist(4, 1e9);

    dist[start] = 0;
    pq.push({start, 0, h(start)});

    while (!pq.empty()) {
        Node u = pq.top();
        pq.pop();

        if (u.id == goal)
            return u.g;

        for (auto& e : graph[u.id]) {
            int v = e.to;
            int w = e.cost;
            int newG = u.g + w;
            int newF = newG + h(v);

            if (newG < dist[v]) {
                dist[v] = newG;
                pq.push({v, newG, newF});
            }
        }
    }

    return -1;
}

int main() {
    cout << "Cost: " << Astar(0, 3);
    return 0;
}
