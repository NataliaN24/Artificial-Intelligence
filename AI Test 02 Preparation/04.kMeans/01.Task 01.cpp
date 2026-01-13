#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <random>
#include <cmath>
#include <limits>


using namespace std;
struct Point
{
	double x, y;
};


double euclidianDis(const Point& a, const Point& b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

bool assignCluster(const vector<Point>& points, const vector<Point>& centers, vector<int>& labels)
{

	bool changed = false;

	for (int i = 0; i < (int)points.size(); i++)
	{
		double bestDist = numeric_limits<double>::infinity();
		int bestK = -1;
		for (int j = 0; j < (int)centers.size(); j++)
		{
			double dist = euclidianDis(points[i], centers[j]);
			if (dist < bestDist)
			{
				bestDist = dist;
				bestK = j;
			}
		}
		if (labels[i] != bestK)
		{
			labels[i] = bestK;
			changed = true;
		}

	}
	return changed;
}

void updateCenters(const vector<Point>& points, vector<Point>& centers, const vector<int>& labels, int k)
{
	vector<double>sumX(k, 0.0);
	vector<double>sumY(k, 0.0);
	vector<int> count(k, 0);


	for (int i = 0; i < (int)points.size(); i++)
	{
		int k = labels[i];

		sumX[k] += points[i].x;
		sumY[k] += points[i].y;
		count[k]++;

	}

	for (int i = 0; i < k; i++)
	{
		if (count[i] > 0)
		{
			centers[i].x = sumX[i] / count[i];
			centers[i].y = sumY[i] / count[i];
		}
	}

}




int main()
{
	int n,k,t;
	cin >> n >> k >> t;
	vector<Point>points(n);
	for (int i = 0; i < n; i++)
	{
		cin >> points[i].x >> points[i].y;
	}
	
	vector<Point>centers(k);
	for (int i = 0; i < k; i++)
	{
		centers[i] = points[i];
	}

	vector<int>labels(n, -1);

	for (int iter = 0; iter < t; iter++)
	{
		bool changed = assignCluster(points, centers, labels);
		if (!changed)break;//no change
		updateCenters(points, centers, labels, k);

	}
	cout << fixed << setprecision(6);
	for (int i = 0; i < k; i++) {
		cout << centers[i].x << " " << centers[i].y << "\n";
	}

	// N lines: label for each point (0..K-1)
	for (int i = 0; i < n; i++) {
		cout << labels[i] << "\n";
	}

	return 0;
}
