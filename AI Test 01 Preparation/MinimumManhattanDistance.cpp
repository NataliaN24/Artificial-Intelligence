You are given a list of points on a 2D plane:

points[i] = [xi, yi]


Your task is to:

Return the minimum Manhattan distance between ANY two points.

The Manhattan distance between (x1, y1) and (x2, y2) is:

|x1 - x2| + |y1 - y2|

📘 Example 1

Input:

points = [[1,2], [3,4], [2,1], [7,0]]


Output:

2


Explanation:

Distances:

between (1,2) and (2,1) → |1−2| + |2−1| = 2

between (3,4) and (2,1) → |3−2| + |4−1| = 4

etc.

Minimum = 2

  #include<iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

int manhattanDistance(int x1,int y1,int x2,int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}

int minManhattanDistance(vector<vector<int>>& arr)
{
	int minDistance = INT32_MAX;
	int calculatedDistance = 0;
	for (int i = 0; i < arr.size()-1; i++)
	{
		for (int j = i + 1; j < arr.size(); j++)
		{
			 calculatedDistance = manhattanDistance(arr[i][0], arr[i][1], arr[j][0], arr[j][1]);
			 minDistance = min(minDistance, calculatedDistance);

		}
	}
	return minDistance;
}

int main()
{
	int n;
	cin >> n;
	vector<vector<int>>arr;
	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		arr.push_back({ a,b });
	}
	cout << minManhattanDistance(arr);

}
