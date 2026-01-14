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
	double x, y;
	string label;
};

bool cmp(const pair<double,string>&a,const pair<double ,string>&b)
{
	return a.first < b.first;
}

double getEuclidianDist(const Point&a,const Point&b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

string weightedKnn(const vector<Point>& train, int k, const Point& test,double epsilon)
{
	int size = (int)train.size();
	if (size == 0) return "";
	if (k <= 0) return "";
	if (k > size) k = size;

	vector<pair<double, string>>res(size);
	for (int i = 0; i < size; i++)
	{
		double dist = getEuclidianDist(train[i], test);
		if (dist == 0.0)return train[i].label;//exact match
		res[i] = { dist,train[i].label };
	}
	sort(res.begin(), res.end(), cmp);

	unordered_map<string, double>score; //class ->sum of weights

	for (int i = 0; i < k; i++)
	{
		double dist = res[i].first;
		double w = 1.0 / (dist + epsilon);
		score[res[i].second]+=w;
	}

	string bestLabelPredict = "";
	double bestScore = -1.0;

	for (const auto& p : score)
	{
		if (p.second > bestScore)
		{
			bestScore = p.second;
			bestLabelPredict = p.first;
		}
	}
	return bestLabelPredict;
}

vector<vector<Point>>splitIntoFolds(const vector<Point>& data, int folds, int seed)
{
	int n = (int)data.size();
	folds = min(folds, n);

	vector<Point>copyData;
	mt19937 rng(seed);
	shuffle(copyData.begin(), copyData.end(), rng);

	vector<vector<Point>>res(folds);
	for (int i = 0; i < n; i++)
	{
		res[i % folds].push_back(copyData[i]);
	}
	return res;
}

double accuracyForFold(const vector<vector<Point>>& foldsData, int testIndex, int k, double epsilon)
{
	vector<Point>trainSet;
	const vector<Point>testSet = foldsData[testIndex];
	for (int i = 0; i < (int)foldsData.size(); i++)
	{
		if (i == testIndex)continue;
		for (int j = 0; j < (int)foldsData[i].size(); j++)
		{
			trainSet.push_back(foldsData[i][j]);
		}
	}
	int correct = 0;
	for (int i = 0; i < (int)testSet.size(); i++)
	{
		string predict = weightedKnn(trainSet, k, testSet[i], epsilon);
		if (predict == testSet[i].label)
		{
			correct++;
		}
	}
	if (testSet.empty()) return 0.0;
	return (double)correct / (double)testSet.size();

}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	vector<Point> data(n);
	for (int i = 0; i < n; i++)
	{
		cin >> data[i].x >> data[i].y >> data[i].label;
	}

	int k, folds;
	double epsilon;
	cin >> k >> folds >> epsilon;

	int seed = 42;

	vector<vector<Point>> foldsData = splitIntoFolds(data, folds, seed);

	double sumAcc = 0.0;
	for (int i = 0; i < (int)foldsData.size(); i++)
	{
		double acc = accuracyForFold(foldsData, i, k, epsilon);
		sumAcc += acc;

		cout << "Fold " << (i + 1) << " accuracy: "
			<< fixed << setprecision(4) << acc << "\n";
	}

	double avg = sumAcc / (double)foldsData.size();
	cout << "Average accuracy: " << fixed << setprecision(4) << avg << "\n";

	return 0;
}
