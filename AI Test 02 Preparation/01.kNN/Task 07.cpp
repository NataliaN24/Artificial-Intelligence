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

vector<vector<Point>> splitIntoFolds(const vector<Point>&trainData,int folds, int seed)
{
	int size = (int)trainData.size();
	folds = min(folds, (int)trainData.size());

	vector<Point> copyData = trainData;
	mt19937 rng(seed);
	shuffle(copyData.begin(), copyData.end(), rng);

	vector<vector<Point>>res(folds);
	for (int i = 0; i < size; i++)
	{
		res[i % folds].push_back(copyData[i]);
	}
	return res;
}

double getAccuracy(const vector<vector<Point>>& folds, int testIndex, int k)
{
	vector<Point>trainSet;
	vector<Point> testSet = folds[testIndex];
	for (int i = 0; i < (int)folds.size(); i++)
	{
		if (i == testIndex)continue;

		for (int j = 0; j < (int)folds[i].size(); j++)
		{
			trainSet.push_back(folds[i][j]);
		}

	}
	int correct = 0;
	for (const auto& testPoint : testSet)
	{
		string predicted = knn(trainSet, testPoint, k);
		if (predicted == testPoint.label)
		{
			correct++;
		}
	}
	if (testSet.empty())return 0.0;
	return (double)correct / testSet.size();
}
int main()
{
	int n;
	cin >> n;

	vector<Point> data(n);
	for (int i = 0; i < n; i++)
	{
		cin >> data[i].x >> data[i].y >> data[i].label;
	}

	int k;
	cin >> k;

	int folds;
	cin >> folds;

	int seed = 42;

	// 1) split into folds
	vector<vector<Point>> foldData = splitIntoFolds(data, folds, seed);

	// 2) evaluate each fold
	double sumAcc = 0.0;

	for (int i = 0; i < (int)foldData.size(); i++)
	{
		double acc = getAccuracy(foldData, i, k);
		sumAcc += acc;

		cout << "Fold " << (i + 1) << " accuracy: "
			<< fixed << setprecision(4) << acc << "\n";
	}

	// 3) average
	double avg = sumAcc / (int)foldData.size();
	cout << "Average accuracy: " << fixed << setprecision(4) << avg << "\n";

	return 0;
}
