Find Overlapping Values Between Two Vectors

You are given two integer vectors:

A = {1, 4, 5, 7, 9}
B = {2, 4, 6, 7, 10}
  #include<iostream>
#include<vector>
#include<queue>
#include <cmath>
#include <algorithm>
using namespace std;


vector<int> findOverlap(const vector<int>& a, const vector<int>& b)
{
    vector<int>res;
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
        {
            if (a[i] == b[j])
            {
                bool exists = false;
                for (int x : res)
                {
                    if (x == a[i])
                    {
                        exists = true;
                        break;
                    }
                }
                if (!exists)
                {
                    res.push_back(a[i]);
                }
               
            }
        }
    }
    return res;
}
int main()
{
    int n, m;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; i++)
        cin >> b[i];

    vector<int> result = findOverlap(a, b);

    for (int x : result)
        cout << x << " ";

    return 0;
}
