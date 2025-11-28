What Hamming Distance Really Means

Hamming distance measures:

“How many positions are different between two strings of equal length.”

That’s it.

If two chromosomes differ in 3 gene positions → the Hamming distance is 3.


#include<iostream>
#include<vector>
#include<queue>
#include <cmath>
#include <algorithm>
using namespace std;

int HammingDistance(const vector<int>& a, const vector<int>& b)
{
    if (a.size() != b.size()) {
        return -1;
    }
    int count = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
        {
            count++;
        }
    }
    return count;
}
int main()
{
    int n;
    cin >> n;

    vector<int> A(n);
    for (int i = 0; i < n; i++)
        cin >> A[i];

    vector<int> B(n);
    for (int i = 0; i < n; i++)
        cin >> B[i];
    cout << HammingDistance(A, B);

    return 0;
}
