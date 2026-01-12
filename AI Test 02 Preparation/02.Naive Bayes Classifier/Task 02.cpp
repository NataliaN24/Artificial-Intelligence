#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <random>
#include <cmath>

using namespace std;

struct sample
{
    char freeWord;   // 'y' or 'n'
    string label;    // "spam" or "ham"
};

struct model
{
    unordered_map<string, int> classCnt;                     // class -> count
    unordered_map<string, unordered_map<char, int>> freeCnt; // class -> (y/n -> count)
    int total = 0;
};

vector<sample> readData()
{
    int n;
    cin >> n;

    vector<sample> res;
    res.reserve(n);

    for (int i = 0; i < n; i++)
    {
        sample s;
        cin >> s.freeWord >> s.label;
        res.push_back(s);
    }
    return res;
}

model train(const vector<sample>& data)
{
    model m;
    m.total = (int)data.size();

    for (int i = 0; i < (int)data.size(); i++)
    {
        m.classCnt[data[i].label]++;
        m.freeCnt[data[i].label][data[i].freeWord]++;
    }
    return m;
}

double prior(model& m, string c)
{
    return (double)m.classCnt[c] / m.total;
}

double likelihood(model& m, string c, char val)
{
    int ccount = m.classCnt[c];
    int vcount = m.freeCnt[c][val];

    // If ccount==0, likelihood is undefined; return 0 to avoid crash.
    if (ccount == 0) return 0.0;

    return (double)vcount / ccount;
}

string predict(model& m, char x)
{
    double scoreSpam = prior(m, "spam") * likelihood(m, "spam", x);
    double scoreHam  = prior(m, "ham")  * likelihood(m, "ham",  x);

    if (scoreSpam >= scoreHam) return "spam";
    return "ham";
}

// Accuracy on a test set
double accuracy(model& m, const vector<sample>& testSet)
{
    int correct = 0;
    for (int i = 0; i < (int)testSet.size(); i++)
    {
        string pred = predict(m, testSet[i].freeWord);
        if (pred == testSet[i].label) correct++;
    }
    if ((int)testSet.size() == 0) return 0.0;
    return (double)correct / (double)testSet.size();
}

// Make stratified folds (by indices)
vector<vector<int>> makeStratifiedFolds(const vector<sample>& data, int k)
{
    vector<int> spamIdx;
    vector<int> hamIdx;

    for (int i = 0; i < (int)data.size(); i++)
    {
        if (data[i].label == "spam") spamIdx.push_back(i);
        else hamIdx.push_back(i);
    }

    // shuffle indices for randomness
    mt19937 rng(42);
    shuffle(spamIdx.begin(), spamIdx.end(), rng);
    shuffle(hamIdx.begin(), hamIdx.end(), rng);

    vector<vector<int>> folds(k);

    // round-robin distribution => stratified
    for (int i = 0; i < (int)spamIdx.size(); i++)
        folds[i % k].push_back(spamIdx[i]);

    for (int i = 0; i < (int)hamIdx.size(); i++)
        folds[i % k].push_back(hamIdx[i]);

    // shuffle inside each fold (optional)
    for (int i = 0; i < k; i++)
        shuffle(folds[i].begin(), folds[i].end(), rng);

    return folds;
}

pair<double,double> meanStd(const vector<double>& vals)
{
    double mean = 0.0;
    for (int i = 0; i < (int)vals.size(); i++) mean += vals[i];
    mean /= (double)vals.size();

    double var = 0.0;
    for (int i = 0; i < (int)vals.size(); i++)
        var += (vals[i] - mean) * (vals[i] - mean);

    var /= (double)vals.size(); // population std
    return {mean, sqrt(var)};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input:
    // n
    // free label
    // ...
    // k
    //
    // Example:
    // 8
    // y spam
    // y spam
    // y spam
    // n spam
    // n ham
    // n ham
    // n ham
    // y ham
    // 4

    vector<sample> data = readData();

    int k;
    cin >> k;

    if (k <= 1) {
        cout << "k must be >= 2\n";
        return 0;
    }
    if (k > (int)data.size()) {
        cout << "k cannot be greater than N\n";
        return 0;
    }

    vector<vector<int>> folds = makeStratifiedFolds(data, k);

    vector<double> foldAcc;
    foldAcc.reserve(k);

    cout << fixed << setprecision(2);

    for (int f = 0; f < k; f++)
    {
        vector<sample> trainSet;
        vector<sample> testSet;

        // build testSet
        for (int i = 0; i < (int)folds[f].size(); i++)
            testSet.push_back(data[folds[f][i]]);

        // build trainSet = all other folds
        for (int j = 0; j < k; j++)
        {
            if (j == f) continue;
            for (int i = 0; i < (int)folds[j].size(); i++)
                trainSet.push_back(data[folds[j][i]]);
        }

        model m = train(trainSet);
        double acc = accuracy(m, testSet);
        foldAcc.push_back(acc);

        cout << "Fold " << (f + 1) << " Accuracy: " << acc * 100.0 << "%\n";
    }

    auto ms = meanStd(foldAcc);
    cout << "\nAverage Accuracy: " << ms.first * 100.0 << "%\n";
    cout << "Standard Deviation: " << ms.second * 100.0 << "%\n";

    return 0;
}
