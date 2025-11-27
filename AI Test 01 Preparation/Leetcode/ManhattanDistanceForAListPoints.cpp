Manhattan Distance for a List of Points

You are given N points, each with coordinates (x, y).

You must compute the total Manhattan distance between
every consecutive pair of points.
  xample

Input points:

(1, 2)
(3, 5)
(3, 1)
(6, 1)


Distances:

(1,2) → (3,5) = |1−3| + |2−5| = 2 + 3 = 5

(3,5) → (3,1) = |3−3| + |5−1| = 0 + 4 = 4

(3,1) → (6,1) = |3−6| + |1−1| = 3 + 0 = 3

Total:

5 + 4 + 3 = 12

  int totalManhattan(const vector<pair<int, int>>& points)
{

    int total = 0;
    for (int i = 0; i < points.size()-1; i++)
    {
        total += abs(points[i].first - points[i + 1].first) + abs(points[i].second - points[i + 1].second);
    }
    return total;
}
int main()
{
    int n;
    cin >> n;

    vector<pair<int,int>> points(n);

    for (int i = 0; i < n; i++)
        cin >> points[i].first >> points[i].second;

    cout << totalManhattan(points);

    return 0;
}
