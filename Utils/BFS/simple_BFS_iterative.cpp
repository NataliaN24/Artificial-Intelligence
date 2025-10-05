#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int N = 100;     // макс брой върхове
vector<int> adj[N];    // списъци на съседство
bool visited[N];       // масив за отбелязване

void bfs(int start) {
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";   // обработваме върха

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
    int n = 5; // брой върхове

    // добавяме ребра (неориентиран граф)
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

    cout << "BFS starting from 0:\n";
    bfs(0);

    return 0;
}
