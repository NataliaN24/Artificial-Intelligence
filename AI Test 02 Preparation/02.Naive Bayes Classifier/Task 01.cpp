#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <iomanip>

using namespace std;

struct table
{
	string outlook;
	string temp;
	string humidity;
	string wind;
	string labelClass;
};

struct model
{
	//to count for each field

	unordered_map<string, int>classCount;
	unordered_map<string, unordered_map<string, int>>outlookcount;//bc we count for e.g., how much sunny do we have for yes
	unordered_map<string, unordered_map<string, int>>tempCount;
	unordered_map<string, unordered_map<string, int>> humidityCount;
	unordered_map<string, unordered_map<string, int>> windCount;

	int totalSamples = 0;

};

model trainNaiveBayes(const vector<table>& data)
{
	model m;
	m.totalSamples = (int)data.size();

	for (const auto& s : data)
	{
		//calculate prior :how many samples for each class :[yes:4] [no:3]
		m.classCount[s.labelClass]++;

		// 2) Likelihood counts: how often each feature value appears inside each class
		m.outlookcount[s.labelClass][s.outlook]++;
		m.tempCount[s.labelClass][s.temp]++;
		m.humidityCount[s.labelClass][s.humidity]++;
		m.windCount[s.labelClass][s.wind]++;

	}
	return m;

}




vector<table>readData()
{
	int n;
	cin >> n;
	vector<table>res;
	res.reserve(n);

	for (int i = 0; i < n; i++)
	{
		table t;
		cin >> t.outlook >> t.temp >> t.humidity >> t.wind >> t.labelClass;
		res.push_back(t);

	}
	return res;

}
table readTestDate()
{
	table s;
	cin >> s.outlook >> s.temp >> s.humidity >> s.wind;
	s.labelClass = "";//unknown ,we need to find this !
	return s;

}

//predicition

double safeLikelihood(int valueCountInClass, int totalClassCount)
{
	if (totalClassCount == 0) return 0.0;
	return (double)valueCountInClass / (double)totalClassCount;
}

unordered_map<string, double>computeScores( model& m, const table& testData)
{
	unordered_map<string, double> scores;
	// For each class, compute:
	// score(C) = P(C) * P(outlook|C) * P(temp|C) * P(humidity|C) * P(wind|C)

	for (const auto& p : m.classCount)
	{
		const string& label = p.first;
		int count = p.second;

		//prior
		double score = (double)count / (double)m.totalSamples;

		score *= safeLikelihood(m.outlookcount[label][testData.outlook], count);
		score *= safeLikelihood(m.tempCount[label][testData.temp], count);
		score *= safeLikelihood(m.windCount[label][testData.wind], count);
		score *= safeLikelihood(m.humidityCount[label][testData.humidity], count);

		scores[label] = score;

	}
	return scores;

}

string argmax(const unordered_map<string, double>& scores)
{
	string best = "";//we still dont know
	double bestScore = -1.0;

	for (const auto& a : scores)
	{
		if (a.second > bestScore)
		{
			bestScore = a.second;
			best = a.first;
		}
	}
	return best;
}

void printscores(const unordered_map<string,double>& scores)

{
	cout << fixed << setprecision(10);
	cout << "Scores:\n";
	for (const auto& kv : scores)
	{
		cout << kv.first << " -> " << kv.second << "\n";
	}

}


int main()
{
	vector<table>trainData = readData();
	model m = trainNaiveBayes(trainData);
	table s = readTestDate();
	auto scores = computeScores(m, s);
	printscores(scores);

	string predicted = argmax(scores);
	cout << "Predicted class: " << predicted << "\n";

}
