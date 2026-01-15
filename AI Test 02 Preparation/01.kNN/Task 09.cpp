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

struct Data
{
    vector<double>mNums;
    int label;
};

void minMaxNormalization( vector<Data>&sample)
{
   
    int arrSize = (int)sample.size();
    int featureSize = (int)sample[0].mNums.size();
    vector<double> maxArr(featureSize, -DBL_MAX);  // или numeric_limits<double>::lowest()
    vector<double> minArr(featureSize, DBL_MAX);  // или numeric_limits<double>::max()

    for (int i = 0; i < arrSize; i++)
    {
        for (int j = 0; j < featureSize; j++)
        {
            maxArr[j] = max(maxArr[j], sample[i].mNums[j]);
            minArr[j] = min(minArr[j], sample[i].mNums[j]);
        }

    }
    for (int i = 0; i < arrSize; i++) {
        for (int j = 0; j < featureSize; j++) {
            double diff = maxArr[j] - minArr[j];
            if (diff == 0.0) {
                sample[i].mNums[j] = 0.0;
                continue;
            }
            sample[i].mNums[j] = (sample[i].mNums[j] - minArr[j]) / diff;
        }
    }
}
double euclidianDist(const Data&a,const Data&b)
{
    if (a.mNums.size() != b.mNums.size())return 1e100;
    double sum = 0.0;
    for (int i = 0; i < a.mNums.size(); i++)
    {
       sum+=( a.mNums[i] - b.mNums[i])* (a.mNums[i] - b.mNums[i]);
    }
    return sqrt(sum);
}
bool compare(const pair<double, int>& a, const pair<double, int>& b) {
    return a.first < b.first; // сортира по дистанция
}

int knnPredict(const vector<Data>& train, const Data& test, int k)
{
    vector<pair<double, int>> dist(train.size());
    for (int i = 0; i < (int)train.size(); i++) {
        dist[i] = { euclidianDist(train[i], test), train[i].label };
    }


    sort(dist.begin(), dist.end(), compare);
    k = min(k, (int)dist.size());


    unordered_map<int, int>cnt;
    for (int i = 0; i < k; i++)
    {
        cnt[dist[i].second]++;

    }

    int bestLabel = -1;
    int bestCount = -1;

    for (const auto& p : cnt) {
        if (p.second > bestCount || (p.second == bestCount && p.first < bestLabel)) {
            bestCount = p.second;
            bestLabel = p.first;
        }
    }
    return bestLabel;

}

double getAccuracy(const vector<Data>& train, const vector<Data>& test, int k)
{
    int correct = 0;

    for (int i = 0; i < (int)test.size(); i++)
    {
        int pred = knnPredict(train, test[i], k);
        if (pred == test[i].label) correct++;
    }

    return test.empty() ? 0.0 : (double)correct / (double)test.size();
}

void trainTestSplit(const vector<Data>& all,
    vector<Data>& train,
    vector<Data>& test,
    double ratio = 0.8)
{
    int n = (int)all.size();
    vector<int>idx(n);
    for (int i = 0; i < n; i++)
    {
        idx[i] = i;
    }
    mt19937 rng(42);
    shuffle(idx.begin(), idx.end(), rng);

    int trainSize = (int)(ratio * n);
    train.clear();
    test.clear();
    for (int i = 0; i < n; i++)
    {
        if (i < trainSize)
        {
            train.push_back(all[idx[i]]);
        }
        else
        {
            test.push_back(all[idx[i]]);
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nSamples, mFeatures;
    cin >> nSamples >> mFeatures;

    vector<Data> samples(nSamples);
    for (int i = 0; i < nSamples; i++) {
        samples[i].mNums.resize(mFeatures);
        for (int j = 0; j < mFeatures; j++) {
            cin >> samples[i].mNums[j];
        }
        cin >> samples[i].label;
    }

    int k;
    cin >> k;

    int useNorm;
    cin >> useNorm; // 0 or 1

 
    vector<Data> train, test;
    trainTestSplit(samples, train, test, 0.8);

    if (train.empty() || test.empty()) {
        cout << "Not enough data for split.\n";
        return 0;
    }

    if (k < 1) k = 1;
    if (k > (int)train.size()) k = (int)train.size();

    if (useNorm == 1) {
        // ОПРОСТЕНО: нормализира отделно train и test
        minMaxNormalization(train);
        minMaxNormalization(test);
    }

    double testAcc = getAccuracy(train, test, k);
    cout << "Test Accuracy (80/20 split) = " << testAcc << "\n";

    return 0;
}
