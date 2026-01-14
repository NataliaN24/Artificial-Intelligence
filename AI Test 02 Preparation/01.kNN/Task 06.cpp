#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <random>
#include <cmath>
#include <limits>
#include<utility>

using namespace std;

struct Point
{
	double x;
	double y;
	string label;
};

double euclidianDist(const Point&a, const Point&b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}
bool compare(const pair<double, string>& a, const pair<double, string>& b)
{
	return a.first < b.first;
}
string knn(const vector<Point>& arr,const Point&p, int k)
{

	if (k <= 0) return "";
	if (k > (int)arr.size()) k = (int)arr.size();

	vector<pair<double, string>>distLabelArr((int)arr.size());
	for (int i = 0; i < (int)arr.size(); i++)
	{
		double dist=euclidianDist(arr[i], p);
		distLabelArr[i] = { dist,arr[i].label };
	}
	sort(distLabelArr.begin(), distLabelArr.end(),compare);
	unordered_map<string, int>count;

	for (int i = 0; i < k; i++)
	{
		count[distLabelArr[i].second]++;
	}

	int maxCount = -1;
	string bestClass = "";
	for (const auto& p:count)
	{
		if (p.second > maxCount)
		{
			maxCount = p.second;
			bestClass = p.first;
		}
	}
	return bestClass;
}

int main()
{
	int n;
	cin >> n;
	vector<Point> arr(n);
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i].x >> arr[i].y >> arr[i].label;
	}
	Point testPoint;
	cin >> testPoint.x >> testPoint.y;
	testPoint.label = "";
	int k;
	cin >> k;
	string predicted = knn(arr, testPoint, k);
	cout << predicted << "\n";

}
