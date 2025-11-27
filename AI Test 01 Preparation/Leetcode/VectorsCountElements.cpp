Count how many elements from vector A appear in vector B

You are given two integer vectors:

A = {3, 8, 5, 2}
B = {1, 3, 9, 5, 3, 7}

#include<iostream>
#include<vector>
#include<queue>
#include <cmath>
#include <algorithm>
using namespace std;

int countMatches(const vector<int>& A, const vector<int>& B)
{
    int count = 0;
    for (int i = 0; i < A.size(); i++)
    {
        bool found = false;
        for (int j = 0; j < B.size(); j++)
        {
            if (A[i] == B[j])
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            count++;
        }
    }
    return count;
}
int main()
{
    int n, m;
    cin >> n;

    vector<int> A(n);
    for (int i = 0; i < n; i++)
        cin >> A[i];

    cin >> m;
    vector<int> B(m);
    for (int i = 0; i < m; i++)
        cin >> B[i];

    cout << countMatches(A, B);

    return 0;
}
