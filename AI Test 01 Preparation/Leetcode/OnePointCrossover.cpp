One-Point Crossover (Very Common Exam Question)

You are given two parent chromosomes of equal length:

Parent 1: 1 2 3 4 5 6
Parent 2: 6 5 4 3 2 1


and a crossover point:

crossoverPoint = 3


where the point means:
copy elements 0,1,2 from parent1
and
copy elements 3,4,5 from parent2.

  #include<iostream>
#include<vector>
#include<queue>
#include <cmath>
#include <algorithm>
using namespace std;

vector<int> onePointCrossover(const vector<int>& p1,
    const vector<int>& p2,
    int point)
{
    vector<int>child;
    for (int i = 0; i <= point; i++)
    {
        child.push_back(p1[i]);
    }
    for (int i = point + 1; i < p2.size(); i++)
    {
        child.push_back(p2[i]);
    }
    return child;
}


int main()
{
    int n, point;
    cin >> n;

    vector<int> p1(n), p2(n);

    for (int i = 0; i < n; i++)
        cin >> p1[i];

    for (int i = 0; i < n; i++)
        cin >> p2[i];

    cin >> point; // crossover point

    vector<int> child = onePointCrossover(p1, p2, point);

    for (int x : child)
        cout << x << " ";

    return 0;
}
