#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <random>
#include <cmath>

using namespace std;

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


int main()
{
	vector<pair<int, int>>cases;
	int n;
	cin >> n;
	cout << fixed << setprecision(4);

	for (int i = 0; i < n; i++) {
		int a, b; // a is +, b is -
		cin >> a >> b;

		cases.push_back({ a, b });

		double h = entropy(a, b);
		cout << "Case " << (i + 1) << " (" << a << "+, " << b << "-): "
			<< "Entropy = " << h << "\n";
	}


}
