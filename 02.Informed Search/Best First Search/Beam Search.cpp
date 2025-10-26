#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

// Graph structure: adjacency list
struct Edge {
    string to;
    int cost;
};

unordered_map<string, vector<Edge>> graph = {
    {"A", {{"B", 2}, {"C", 5}, {"D", 3}}},
    {"B", {{"E", 4}, {"F", 6}}},
    {"C", {{"G", 2}, {"H", 8}}},
    {"D", {{"I", 3}, {"J", 5}}},
    {"E", {}}, {"F", {}}, {"G", {}}, {"H", {}}, {"I", {}}, {"J", {}}
};

// Heuristic values (h)
unordered_map<string, int> heuristic = {
    {"A", 10}, {"B", 7}, {"C", 8}, {"D", 6},
    {"E", 4}, {"F", 5}, {"G", 3}, {"H", 9},
    {"I", 2}, {"J", 1}
};

// Node structure
struct Node {
    string name;
    int f;
    vector<string> path;
};

// Comparator for sorting nodes by f
bool compareNodes(const Node& a, const Node& b) {
    return a.f < b.f;
}

// Beam Search algorithm
void beamSearch(const string& start, const string& goal, int beamWidth) {
    vector<Node> currentLevel;
    currentLevel.push_back({start, heuristic[start], {start}});

    while (!currentLevel.empty()) {
        // Expand all nodes in the current beam
        vector<Node> nextLevel;

        for (auto& node : currentLevel) {
            if (node.name == goal) {
                cout << "Goal found! Path: ";
                for (auto& n : node.path) cout << n << " ";
                cout << endl;
                return;
            }

            // Generate successors
            for (auto& edge : graph[node.name]) {
                vector<string> newPath = node.path;
                newPath.push_back(edge.to);
                int f = heuristic[edge.to];  // only heuristic used
                nextLevel.push_back({edge.to, f, newPath});
            }
        }

        if (nextLevel.empty()) break;

        // Sort all successors by heuristic and keep the best beamWidth nodes
        sort(nextLevel.begin(), nextLevel.end(), compareNodes);
        if ((int)nextLevel.size() > beamWidth)
            nextLevel.resize(beamWidth);

        // Move to next level
        currentLevel = nextLevel;
    }

    cout << "No path found.\n";
}

int main() {
    string start = "A";
    string goal = "I";
    int beamWidth = 2; // number of nodes to keep at each level

    cout << "Beam Search (width = " << beamWidth << ")\n";
    beamSearch(start, goal, beamWidth);

    return 0;
}
