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
struct Point
{
	double x, y;
	string label;
};

double euclidianDist(const Point& a, const Point& b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}
bool cmp(const pair<double,string>&a, const pair<double, string>& b)
{
	return a.first < b.first;

}
string knnPredict(const vector<Point>& arr, const Point& p, int k)
{
	vector<pair<double, string>>res(arr.size());
	k = min(k, (int)arr.size());

	for (int i = 0; i < (int)arr.size(); i++)
	{
		double dist = euclidianDist(arr[i], p);
		res[i] = { dist,arr[i].label };	
	}
	sort(res.begin(), res.end(), cmp);
	unordered_map<string, int>count;
	for (int i = 0; i < k; i++)
	{
		count[res[i].second]++;
	}

	string bestLabel = "";
	int cnt = -1;
	for (const auto& p : count)
	{
		if (p.second > cnt)
		{
			cnt = p.second;
			bestLabel = p.first;
		}
	}
	return bestLabel;
}

double getAcurracy(const vector<Point>& arr,int k)
{
	int correct = 0;
	
	for (int i = 0; i < arr.size(); i++)
	{
		vector<Point>train;
		train.reserve(arr.size() - 1);
		for (int j = 0; j < arr.size(); j++)
		{
			if (i != j)
			{
				train.push_back(arr[j]);
			}
		}
		int kk = min(k, (int)train.size());
		string predicted = knnPredict(train, arr[i], kk);

		if (predicted == arr[i].label)
		{
			correct++;
		}
	}
	return (double)correct / (double)arr.size();
}

void normalizeTrainTest(vector<Point>& train, Point& test)
{
	vector<double> xOnly(train.size());
	vector<double> yOnly(train.size());

	for (int i = 0; i < (int)train.size(); i++)
	{
		xOnly[i] = train[i].x;
		yOnly[i] = train[i].y;
	}

	double maxX = *max_element(xOnly.begin(), xOnly.end());
	double minX = *min_element(xOnly.begin(), xOnly.end());
	double maxY = *max_element(yOnly.begin(), yOnly.end());
	double minY = *min_element(yOnly.begin(), yOnly.end());

	double dx = maxX - minX;
	double dy = maxY - minY;

	for (int i = 0; i < (int)train.size(); i++)
	{
		train[i].x = (dx == 0.0) ? 0.0 : (train[i].x - minX) / dx;
		train[i].y = (dy == 0.0) ? 0.0 : (train[i].y - minY) / dy;
	}

	test.x = (dx == 0.0) ? 0.0 : (test.x - minX) / dx;
	test.y = (dy == 0.0) ? 0.0 : (test.y - minY) / dy;
}

vector<vector<Point>> makeStratifiedFolds(const vector<Point>& data, int kFolds, unsigned seed)
{
	unordered_map<string, vector<Point>> byClass;
	for (int i = 0; i < (int)data.size(); i++)
	{
		byClass[data[i].label].push_back(data[i]);
	}

	mt19937 rng(seed);
	vector<vector<Point>> folds(kFolds);

	for (auto& kv : byClass)
	{
		vector<Point>& cls = kv.second;
		shuffle(cls.begin(), cls.end(), rng);

		for (int i = 0; i < (int)cls.size(); i++)
		{
			folds[i % kFolds].push_back(cls[i]);
		}
	}

	for (int i = 0; i < kFolds; i++)
	{
		shuffle(folds[i].begin(), folds[i].end(), rng);
	}

	return folds;
}
double kFoldsAccuracy(const vector<Point>& data, int kFolds, int k, unsigned seed)
{
	if (kFolds <= 1) return 0.0;

	vector<vector<Point>> folds = makeStratifiedFolds(data, kFolds, seed);

	double sumAcc = 0.0;
	int usedFolds = 0;

	for (int i = 0; i < kFolds; i++)
	{
		vector<Point> test = folds[i];
		vector<Point> train;

		// build train = all folds except i
		int trainSize = 0;
		for (int j = 0; j < kFolds; j++)
			if (j != i) trainSize += (int)folds[j].size();

		train.reserve(trainSize);

		for (int j = 0; j < kFolds; j++)
		{
			if (j == i) continue;
			for (int t = 0; t < (int)folds[j].size(); t++)
				train.push_back(folds[j][t]);
		}

		if (train.empty() || test.empty()) continue;

		// normalize inside the fold (fit from train, apply to train+test)
		normalizeTrainTest(train, test);

		int kk = min(k, (int)train.size());
		int correct = 0;

		for (int t = 0; t < (int)test.size(); t++)
		{
			string pred = knnPredict(train, test[t], kk);
			if (pred == test[t].label) correct++;
		}

		sumAcc += (double)correct / (double)test.size();
		usedFolds++;
	}

	return (usedFolds == 0) ? 0.0 : (sumAcc / (double)usedFolds);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m; // m не се ползва (оставям го)

	vector<Point> input(n);
	for (int i = 0; i < n; i++)
		cin >> input[i].x >> input[i].y >> input[i].label;

	Point test;
	cin >> test.x >> test.y;
	test.label = "";

	int k;
	cin >> k;

	normalizeTrainTest(input, test);

	int kPred = min(k, (int)input.size());
	cout << knnPredict(input, test, kPred) << "\n";

	return 0;
}
