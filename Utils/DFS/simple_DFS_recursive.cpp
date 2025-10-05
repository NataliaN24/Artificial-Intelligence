#include <iostream>
#include <vector>
using namespace std;

const int N = 100;         // макс брой върхове
vector<int> adj[N];        // списъци на съседство
bool visited[N];           // масив за отбелязване

void dfs(int u) {
    visited[u] = true;
    cout << u << " ";      // обработка на върха (тук просто печатаме)

    for (int v : adj[u]) { // минаваме през съседите
        if (!visited[v]) {
            dfs(v);        // влизаме по-надълбоко
        }
    }
}

int main() {
    int n = 5; // брой върхове
    // Добавяме ребра (неориентиран граф)
    adj[0].push_back(1);
    adj[0].push_back(4);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[1].push_back(3);
    adj[1].push_back(4);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);
    adj[3].push_back(2);
    adj[3].push_back(4);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[4].push_back(3);

    cout << "DFS starting from vertex 0:\n";
    dfs(0);

    return 0;
}
