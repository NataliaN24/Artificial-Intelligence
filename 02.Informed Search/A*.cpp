#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// Graph edge
struct Edge {
    string to;
    int cost;
};

// Graph (adjacency list)
unordered_map<string, vector<Edge>> graph = {
    {"A", {{"B", 1}, {"C", 4}}},
    {"B", {{"C", 2}, {"D", 5}}},
    {"C", {{"D", 1}}},
    {"D", {}}
};

// Heuristic h(n)
unordered_map<string, int> heuristic = {
    {"A", 7}, {"B", 6}, {"C", 2}, {"D", 0}
};

// Node for priority queue
struct Node {
    string name;
    int g;                // cost so far
    int f;                // total estimated cost (f = g + h)
    vector<string> path;  // path taken so far

    bool operator<(const Node& other) const {
        return f > other.f; // smaller f has higher priority
    }
};

// A* Search
void aStarSearch(const string& start, const string& goal) {
    priority_queue<Node> open; // priority queue sorted by f
    unordered_map<string, int> bestCost; // best g found so far

    open.push({start, 0, heuristic[start], {start}});
    bestCost[start] = 0;

    while (!open.empty()) {
        Node current = open.top();
        open.pop();

        // Goal check
        if (current.name == goal) {
            cout << "Goal found! Path: ";
            for (auto& n : current.path) cout << n << " ";
            cout << "\nTotal cost: " << current.g << endl;
            return;
        }

        // Explore neighbors
        for (auto& edge : graph[current.name]) {
            int newCost = current.g + edge.cost;
            int f = newCost + heuristic[edge.to];

            // Only consider this path if it's better
            if (!bestCost.count(edge.to) || newCost < bestCost[edge.to]) {
                bestCost[edge.to] = newCost;
                vector<string> newPath = current.path;
                newPath.push_back(edge.to);
                open.push({edge.to, newCost, f, newPath});
            }
        }
    }

    cout << "No path found.\n";
}

int main() {
    string start = "A";
    string goal = "D";

    cout << "A* Search from " << start << " to " << goal << ":\n";
    aStarSearch(start, goal);

    return 0;
}
