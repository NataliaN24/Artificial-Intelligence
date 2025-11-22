#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int INF = 1e9;
int goal;

// примерен граф (няколко възела)
vector<vector<int>> graph = {
    {1, 2},   // съседите на 0
    {3},      // съседите на 1
    {3},      // съседите на 2
    {}        // съседите на 3
};

// примерна цена на ребрата
int cost(int a, int b) {
    // 0->1 = 2, 0->2 = 5, 1->3 = 1, 2->3 = 2
    if (a == 0 && b == 1) return 2;
    if (a == 0 && b == 2) return 5;
    if (a == 1 && b == 3) return 1;
    if (a == 2 && b == 3) return 2;
    return 1e9;
}

// примерна евристика h(n)
int h(int node) {
    int heuristics[] = {4, 2, 3, 0};
    return heuristics[node];
}

int dfs_ida(int node, int g, int bound) {
    int f = g + h(node);
    if (f > bound) return f;
    if (node == goal) return -1;  // намерено

    int min_exceed = INF;

    for (int nxt : graph[node]) {
        int t = dfs_ida(nxt, g + cost(node, nxt), bound);

        if (t == -1) return -1;     // намерихме решение
        if (t < min_exceed) min_exceed = t; // най-малкото надвишаване
    }

    return min_exceed;
}

int IDAstar(int start, int Goal) {
    goal = Goal;
    int bound = h(start);

    while (true) {
        int t = dfs_ida(start, 0, bound);
        if (t == -1) return bound;    // FOUND solution
        if (t == INF) return -1;      // няма решение
        bound = t;                    // новият лимит
    }
}

int main() {
    int result = IDAstar(0, 3);
    cout << "Optimal cost path = " << result << endl;
    return 0;
}
