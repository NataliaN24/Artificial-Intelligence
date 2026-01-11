
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point
{
    double x;
    double y;
};
struct Neighbor
{
    double dist;
    double y;
};
double getDist(double x1, double x2)
{
    return fabs(x1 - x2);
}
bool compareNeigh(const Neighbor& a, const Neighbor& b)
{
    return a.dist < b.dist;
}

double knn(vector<Point>arr, double x,int k)
{
    if (arr.empty()) return 0.0;          // or throw
    if (k <= 0) return 0.0;               // or throw
    if (k > (int)arr.size()) k = (int)arr.size();

    vector<Neighbor>neigh;
    neigh.reserve(arr.size());

    for (int i = 0; i < (int)arr.size(); i++)
    {
        Neighbor n;
        n.dist = getDist(arr[i].x, x);
        n.y = arr[i].y;
        neigh.push_back(n);
    }
    sort(neigh.begin(), neigh.end(), compareNeigh);
    double sum = 0.0;

    for (int i = 0; i < k; i++)
    {
        sum += neigh[i].y;
    }
    return sum / k;
}

int main() {
    int n;
    cin >> n;
    vector<Point>arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].x>>arr[i].y;
    }
    int k;
    cin >> k;
    int newX;
    cin >> newX;

    cout << knn(arr, newX, k);
}
