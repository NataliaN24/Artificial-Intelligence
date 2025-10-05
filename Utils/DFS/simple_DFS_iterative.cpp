#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int N = 100;      // макс брой върхове
vector<int> adj[N];     // списъци на съседство
bool visited[N];        // масив за отбелязване

void dfs_iterative(int start) {
    stack<int> st;
    st.push(start);
    visited[start] = true;

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        cout << u << " ";  // обработка на върха

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                st.push(v);
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

    cout << "Iterative DFS starting from 0:\n";
    dfs_iterative(0);

    return 0;
}
