#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

struct Sample {
    double x;
    string label;
};

struct Neighbor {
    double dist;
    string label;
};

double dist1D(double a, double b) {
    return fabs(a - b);
}

bool compareNeighbor(const Neighbor& a, const Neighbor& b) {
    if (a.dist != b.dist) return a.dist < b.dist;
    // deterministic tie-break
    return a.label < b.label;
}

vector<Sample> readDataset() {
    int n;
    cin >> n;
    vector<Sample> data(n);
    for (int i = 0; i < n; i++) {
        cin >> data[i].x >> data[i].label;
    }
    return data;
}

vector<vector<int>> makeFolds(int n, int F) {
    vector<vector<int>> folds(F);
    for (int idx = 0; idx < n; idx++) {
        folds[idx % F].push_back(idx);
    }
    return folds;
}

string knnPredict1D(const vector<Sample>& train, double xt, int k) {
    if (train.empty()) return "ERROR_EMPTY_TRAIN";
    if (k <= 0) return "ERROR_BAD_K";
    if (k > (int)train.size()) k = (int)train.size();

    vector<Neighbor> neigh;
    neigh.reserve(train.size());

    for (int i = 0; i < (int)train.size(); i++) {
        Neighbor nb;
        nb.dist = dist1D(train[i].x, xt);
        nb.label = train[i].label;
        neigh.push_back(nb);
    }

    sort(neigh.begin(), neigh.end(), compareNeighbor);

    // vote using vectors (no map)
    vector<string> labels;
    vector<int> counts;
    vector<double> closest;

    for (int i = 0; i < k; i++) {
        int idx = -1;
        for (int j = 0; j < (int)labels.size(); j++) {
            if (labels[j] == neigh[i].label) { idx = j; break; }
        }

        if (idx == -1) {
            labels.push_back(neigh[i].label);
            counts.push_back(1);
            closest.push_back(neigh[i].dist);
        } else {
            counts[idx]++;
            if (neigh[i].dist < closest[idx]) closest[idx] = neigh[i].dist;
        }
    }

    // choose best: max votes, tie -> smaller closest distance
    string bestLabel = labels[0];
    int bestCount = counts[0];
    double bestClosest = closest[0];

    for (int i = 1; i < (int)labels.size(); i++) {
        if (counts[i] > bestCount ||
            (counts[i] == bestCount && closest[i] < bestClosest)) {
            bestCount = counts[i];
            bestClosest = closest[i];
            bestLabel = labels[i];
        }
    }

    return bestLabel;
}

void buildTrainTest(const vector<Sample>& data,
                    const vector<vector<int>>& folds,
                    int foldIndex,
                    vector<Sample>& train,
                    vector<Sample>& test) {
    train.clear();
    test.clear();

    for (int f = 0; f < (int)folds.size(); f++) {
        for (int j = 0; j < (int)folds[f].size(); j++) {
            int idx = folds[f][j];
            if (f == foldIndex) test.push_back(data[idx]);
            else train.push_back(data[idx]);
        }
    }
}

double computeAccuracyForFold(const vector<Sample>& train,
                             const vector<Sample>& test,
                             int k) {
    if (test.empty()) return 0.0;

    int correct = 0;
    for (int i = 0; i < (int)test.size(); i++) {
        string pred = knnPredict1D(train, test[i].x, k);
        if (pred == test[i].label) correct++;
    }
    return (double)correct / (double)test.size();
}

vector<double> crossValidate(const vector<Sample>& data, int k, int F) {
    vector<vector<int>> folds = makeFolds((int)data.size(), F);
    vector<double> accuracies;
    accuracies.reserve(F);

    vector<Sample> train, test;

    for (int fold = 0; fold < F; fold++) {
        buildTrainTest(data, folds, fold, train, test);
        double acc = computeAccuracyForFold(train, test, k);
        accuracies.push_back(acc);
    }
    return accuracies;
}

double averageAccuracy(const vector<double>& acc) {
    if (acc.empty()) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < (int)acc.size(); i++) sum += acc[i];
    return sum / (double)acc.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Input format:
    // n
    // x label
    // x label
    // ...
    // k
    // F
    //
    // Example:
    // 8
    // 1 A
    // 2 A
    // 3 A
    // 6 B
    // 7 B
    // 8 B
    // 9 B
    // 10 B
    // 3
    // 5

    vector<Sample> data = readDataset();

    int k, F;
    cin >> k >> F;

    vector<double> acc = crossValidate(data, k, F);

    cout << fixed << setprecision(4);
    for (int i = 0; i < (int)acc.size(); i++) {
        cout << "Fold " << (i + 1) << " accuracy: " << acc[i] << "\n";
    }

    cout << "Average accuracy: " << averageAccuracy(acc) << "\n";
    return 0;
}
