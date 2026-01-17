#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <limits>
#include<algorithm>
#include<random>

using namespace std;

struct point
{
	double x, y;
	string label;
};
double getEuclidian(const point& a, const point& b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}
bool cmp(const pair<double,string>&a,const pair<double,string>&b)
{
	return a.first < b.first;

}
string knn(const vector<point>& data, const point& test, int k)
{
	int size = data.size();
	vector<pair<double, string>>arr(size);
	for (int i = 0; i < size; i++)
	{
		double dist = getEuclidian(data[i], test);
		arr[i] = { dist,data[i].label };
	}
	sort(arr.begin(), arr.end(), cmp);
	unordered_map<string, int>count;
	for (int i = 0; i < k; i++)
	{
		count[arr[i].second]++;

	}
	string bestLabel = "";
	int bestSize = -1;
	for (const auto& p : count)
	{
		if (p.second > bestSize)
		{
			bestSize = p.second;
			bestLabel = p.first;
		}

	}

	return bestLabel;



}



int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	vector<point> data(n);
	for (int i = 0; i < n; i++) {
		cin >> data[i].x >> data[i].y >> data[i].label;
	}

	point test;
	cin >> test.x >> test.y;

	int k;
	cin >> k;

	if (n == 0) {
		cout << "No training data\n";
		return 0;
	}

	if (k <= 0) k = 1;
	if (k > n) k = n;

	string predicted = knn(data, test, k);
	cout << predicted << "\n";

	return 0;
}
