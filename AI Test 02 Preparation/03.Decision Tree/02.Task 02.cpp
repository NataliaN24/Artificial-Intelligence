#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <random>
#include <cmath>

using namespace std;

struct Sample
{
	char a;
	char label;
};

double safeLog2(double x)
{
	if (x <= 0.0)return 0.0;
	return log2(x);

}

double entropy(int postive, int negative)
{
	int total = postive + negative;
	if (total == 0)return 0.0;

	double pPos = (double)postive / total;
	double pNeg = (double)negative / total;

	//H=-sum p*log2p

	double H = 0.0;
	H = -pPos * safeLog2(pPos) - pNeg * safeLog2(pNeg);

	/*if (pPos > 0.0) H -= pPos * log2(pPos);
	if (pNeg > 0.0) H -= pNeg * log2(pNeg);*/
	return H;
}

double entropySet(const vector<Sample>&s)
{
	int pos = 0, neg = 0;
	for (const auto& p : s)
	{
		if (p.label == '+')
		{
			pos++;
		}
		else
		{
			neg++;
		}
	}
	return entropy(pos, neg);
}
//split by attribute A

unordered_map<char, vector<Sample>>split(const vector<Sample>& s)
{
	unordered_map<char, vector<Sample>>groups;
	for (const auto& a : s)
	{
		groups[a.a].push_back(a);
	}
	return groups;
}

double informationGain(const vector<Sample>& s)
{
	double h = entropySet(s);
	auto groups = split(s);
	int total = (int)s.size();

	double weightedEntropy = 0.0;
	for (const auto& point : groups)
	{
		double w = (double)point.second.size() / total;
		weightedEntropy += w * entropySet(point.second);
	}
	return h - weightedEntropy;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	vector<Sample> S;
	S.reserve(n);

	for (int i = 0; i < n; i++) {
		Sample x;
		cin >> x.a >> x.label;   // example: T +   or   F -
		S.push_back(x);
	}

	cout << fixed << setprecision(4);

	double Hs = entropySet(S);
	cout << "H(S) = " << Hs << "\n\n";

	auto groups = split(S);

	cout << "Entropies after split by attribute A:\n";
	for (const auto& g : groups) {
		char val = g.first;
		const vector<Sample>& subset = g.second;

		// count pos/neg in subset (optional, but useful for debugging)
		int pos = 0, neg = 0;
		for (const auto& p : subset) {
			if (p.label == '+') pos++;
			else neg++;
		}

		cout << "A=" << val
			<< "  size=" << subset.size()
			<< " (pos=" << pos << ", neg=" << neg << ")"
			<< "  H=" << entropy(pos, neg)
			<< "\n";
	}

	double gain = informationGain(S);
	cout << "\nGain(S, A) = " << gain << "\n";

	return 0;
}
