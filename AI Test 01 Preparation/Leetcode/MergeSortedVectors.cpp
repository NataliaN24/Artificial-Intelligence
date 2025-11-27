Merge Two Sorted Vectors Into One Sorted Vector (Using Only WHILE LOOPS)

#include<iostream>
#include<vector>
#include<queue>
#include <cmath>
#include <algorithm>
using namespace std;

vector<int> mergeSorted(const vector<int>& A, const vector<int>& B)
{

    vector<int>res;
    int i=0, j = 0;
    while (i < A.size() && j < B.size())
    {
        if (A[i] < B[j])
        {
            res.push_back(A[i]);
            i++;
        }
        else
        {
            res.push_back(B[j]);
            j++;
        }
    }
    while (i < A.size())
    {
        res.push_back(A[i]);
        i++;
    }

    while (j < B.size())
    {
        res.push_back(B[j]);
        j++;
    }

    return res;



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

    vector<int> result = mergeSorted(A, B);

    for (int x : result)
        cout << x << " ";

    return 0;
}
