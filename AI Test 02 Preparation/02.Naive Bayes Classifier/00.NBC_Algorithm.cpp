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

struct model
{
	int n = 0;
	int m = 0;
	unordered_map<string, int>countByClass;
	vector<unordered_set<string>>featureValues;
	//featureCounts[атрибут][клас][стойност] = брой
	vector<unordered_map<string, unordered_map<string, int>>> featureCounts;
	//unordered_map<string, int>outlookYes;
	//unordered_map<string, int>outlookNo;
	//unordered_map<string, int>tempYes;
	//unordered_map < string,int> tempNo;
};
model traiveNaiveBayes(const vector<vector<string>>& arr, const vector<string>& labels)
{
	model mod;
	mod.n = arr.size();
	mod.m = arr[0].size();

	mod.featureValues.assign(mod.m, unordered_set<string>());
	mod.featureCounts.assign(mod.m, unordered_map < string, unordered_map < string, int>());

	for (int i = 0; i < mod.n; i++)
	{
		string cls = labels[i];
		mod.countByClass[cls]++;


		for (int j = 0; j < mod.m; j++)
		{
			string val = arr[i][j];
			mod.featureValues[j].insert(val);
			mod.featureCounts[j][cls][val]++;
		}
	}
	return mod;

}
string predict(model mod, const vector<string>& x)
{
	double bestScore = -1.0;
	string bestClass = "";

	for (auto p : mod.countByClass)
	{
		string cls = p.first;
		int classCnt = p.second;

		double score = (double)classCnt / mod.n; // P(Class)

		for (int j = 0; j < mod.m; j++)
		{
			string val = x[j];

			int cntVal = mod.featureCounts[j][cls][val];   // if missing -> 0 (but inserts in copy)
			int Kj = (int)mod.featureValues[j].size();     // number of distinct values for feature j

			// Laplace smoothing: (cnt + 1) / (classCnt + Kj)
			score *= (double)(cntVal + 1) / (classCnt + Kj);
		}

		if (score > bestScore)
		{
			bestScore = score;
			bestClass = cls;
		}
	}

	return bestClass;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<vector<string>> x(n, vector<string>(m));
	vector<string> label(n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> x[i][j];
		}
		cin >> label[i];
	}

	vector<string> test(m);
	for (int j = 0; j < m; j++)
	{
		cin >> test[j];
	}

	model mod = traiveNaiveBayes(x, label);
	cout << predict(mod, test) << "\n";

	return 0;
}
