Apply MINIMAX to a Small Game Tree

You are given the following partial game tree.
MAX is at the root.
GAME TREE (Text Version)
Level 0 (MAX)
            A
          /   \
         B     C

Level 1 (MIN)
B has children: D, E  
C has children: F, G  

Level 2 (Terminal values)

D has children with values: 3, 12

E has children with values: 8, 2

F has children with values: 4, 6

G has children with values: 14, 5

🚨 YOUR TASK

Compute the Minimax value of every internal node:

D, E, F, G (MIN nodes)

B, C (MAX nodes)

A (MAX root)

Show the value that propagates upward at each step.

  #include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minimax(int node, int depth, bool isMax,
            const vector<vector<int>>& tree,
            const vector<int>& values)
{
    // Leaf or depth limit
    if (depth == 0 || tree[node].empty())
        return values[node];

    if (isMax)
    {
        int best = -1000000000;
        for (int child : tree[node])
        {
            best = max(best, minimax(child, depth - 1, false, tree, values));
        }
        return best;
    }
    else
    {
        int best = 1000000000;
        for (int child : tree[node])
        {
            best = min(best, minimax(child, depth - 1, true, tree, values));
        }
        return best;
    }
}

int main()
{
    int n;
    cin >> n;  // number of nodes

    vector<vector<int>> tree(n);
    vector<int> values(n);

    // Input tree structure
    // For each node: number_of_children child1 child2 ...
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        tree[i].resize(k);
        for (int j = 0; j < k; j++)
            cin >> tree[i][j];
    }

    // Input values (-1 for internal nodes)
    for (int i = 0; i < n; i++)
        cin >> values[i];

    int root, depth, type;
    cin >> root >> depth >> type;

    bool isMax = (type == 1); // 1 = MAX, 0 = MIN

    cout << minimax(root, depth, isMax, tree, values);

    return 0;
}
