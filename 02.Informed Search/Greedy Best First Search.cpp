#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <set>
#include <string>

using namespace std;

// Edge structure
struct Edge {
    string to;
    int cost;
};

// Graph: adjacency list
unordered_map<string, vector<Edge>> graph = {
    {"A", {{"B", 2}, {"C", 5}}},
    {"B", {{"D", 4}, {"E", 7}}},
    {"C", {{"F", 2}}},
    {"D", {{"G", 1}}},
    {"E", {{"G", 3}}},
    {"F", {{"G", 6}}},
    {"G", {}}
};

// Heuristic estimates (h-values)
unordered_map<string, int> heuristic = {
    {"A", 10}, {"B", 8}, {"C", 5},
    {"D", 7}, {"E", 3}, {"F", 2}, {"G", 0}
};

// Node for the priority queue
struct Node {
    string name;
    int h;                // heuristic value
    vector<string> path;  // store the path

    bool operator<(const Node& other) const {
        // smaller h has higher priority
        return h > other.h;
    }
};

// Greedy Best-First Search
void greedyBestFirstSearch(const string& start, const string& goal) {
    priority_queue<Node> pq;
    set<string> visited;

    pq.push({start, heuristic[start], {start}});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (visited.count(current.name))
            continue;

        visited.insert(current.name);
        cout << "Visiting: " << current.name << " (h=" << current.h << ")\n";

        if (current.name == goal) {
            cout << "\nPath found:\n";
            for (auto& n : current.path) cout << n << " ";
            cout << endl;
            return;
        }

        for (auto& edge : graph[current.name]) {
            if (!visited.count(edge.to)) {
                vector<string> newPath = current.path;
                newPath.push_back(edge.to);
                pq.push({edge.to, heuristic[edge.to], newPath});
            }
        }
    }

    cout << "No path found.\n";
}

int main() {
    string start = "A";
    string goal = "G";

    cout << "Greedy Best-First Search from " << start << " to " << goal << ":\n\n";
    greedyBestFirstSearch(start, goal);

    return 0;
}
