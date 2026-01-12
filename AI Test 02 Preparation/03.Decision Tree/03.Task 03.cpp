#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <iomanip>
using namespace std;

struct Sample {
    string outlook; // Sunny, Overcast, Rain
    string wind;    // Weak, Strong
    char play;      // 'Y' (Yes) or 'N' (No)
};

double safeLog2(double x) {
    if (x <= 0.0) return 0.0;
    return log2(x);
}

double entropyCounts(int yes, int no) {
    int total = yes + no;
    if (total == 0) return 0.0;

    double pY = (double)yes / total;
    double pN = (double)no / total;

    double H = 0.0;
    if (pY > 0.0) H -= pY * safeLog2(pY);
    if (pN > 0.0) H -= pN * safeLog2(pN);
    return H;
}

double entropySet(const vector<Sample>& S) {
    int yes = 0, no = 0;
    for (const auto& s : S) {
        if (s.play == 'Y') yes++;
        else no++;
    }
    return entropyCounts(yes, no);
}

unordered_map<string, vector<Sample>> splitByOutlook(const vector<Sample>& S) {
    unordered_map<string, vector<Sample>> groups;
    for (const auto& s : S) groups[s.outlook].push_back(s);
    return groups;
}

unordered_map<string, vector<Sample>> splitByWind(const vector<Sample>& S) {
    unordered_map<string, vector<Sample>> groups;
    for (const auto& s : S) groups[s.wind].push_back(s);
    return groups;
}

double informationGainOutlook(const vector<Sample>& S) {
    double Hparent = entropySet(S);
    int total = (int)S.size();

    auto groups = splitByOutlook(S);
    double weighted = 0.0;

    for (const auto& [val, subset] : groups) {
        double w = (double)subset.size() / total;
        weighted += w * entropySet(subset);
    }
    return Hparent - weighted;
}

double informationGainWind(const vector<Sample>& S) {
    double Hparent = entropySet(S);
    int total = (int)S.size();

    auto groups = splitByWind(S);
    double weighted = 0.0;

    for (const auto& [val, subset] : groups) {
        double w = (double)subset.size() / total;
        weighted += w * entropySet(subset);
    }
    return Hparent - weighted;
}

string chooseBestAttribute(const vector<Sample>& S) {
    double gOutlook = informationGainOutlook(S);
    double gWind = informationGainWind(S);

    return (gOutlook >= gWind) ? "Outlook" : "Wind";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Sample> S;
    S.reserve(n);

    for (int i = 0; i < n; i++) {
        Sample s;
        string playStr;
        cin >> s.outlook >> s.wind >> playStr;  // e.g. Sunny Weak No
        s.play = (playStr == "Yes") ? 'Y' : 'N';
        S.push_back(s);
    }

    cout << fixed << setprecision(4);

    double Hs = entropySet(S);
    double gOutlook = informationGainOutlook(S);
    double gWind = informationGainWind(S);
    string best = chooseBestAttribute(S);

    cout << "H(S) = " << Hs << "\n";
    cout << "Gain(S, Outlook) = " << gOutlook << "\n";
    cout << "Gain(S, Wind)    = " << gWind << "\n";
    cout << "Best attribute (root) = " << best << "\n";

    return 0;
}
