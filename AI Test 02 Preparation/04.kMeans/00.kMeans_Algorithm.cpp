#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <algorithm>

using namespace std;

double dist2(const vector<double>& a, const vector<double>& b) {
    double sum = 0.0;
    for (int i = 0; i < (int)a.size(); i++) {
        double d = a[i] - b[i];
        sum += d * d;
    }
    return sum;
}

int closestCenter(const vector<double>& p,
                  const vector<vector<double>>& centers) {
    int best = 0;
    double bestDist = numeric_limits<double>::infinity();

    for (int k = 0; k < (int)centers.size(); k++) {
        double d = dist2(p, centers[k]);
        if (d < bestDist) {
            bestDist = d;
            best = k;
        }
    }
    return best;
}

vector<int> kmeans(const vector<vector<double>>& data,
                   int K, int maxIter = 100) {
    int n = data.size();
    int m = data[0].size();

    vector<int> labels(n, -1);
    vector<vector<double>> centers(K, vector<double>(m));

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, n - 1);

    // init centers (random points)
    for (int k = 0; k < K; k++) {
        centers[k] = data[dis(gen)];
    }

    for (int iter = 0; iter < maxIter; iter++) {
        bool changed = false;

        // assignment step
        for (int i = 0; i < n; i++) {
            int newLabel = closestCenter(data[i], centers);
            if (labels[i] != newLabel) {
                labels[i] = newLabel;
                changed = true;
            }
        }

        // update step
        vector<vector<double>> newCenters(K, vector<double>(m, 0.0));
        vector<int> count(K, 0);

        for (int i = 0; i < n; i++) {
            int k = labels[i];
            for (int j = 0; j < m; j++) {
                newCenters[k][j] += data[i][j];
            }
            count[k]++;
        }

        for (int k = 0; k < K; k++) {
            if (count[k] == 0) {
                newCenters[k] = data[dis(gen)];
            } else {
                for (int j = 0; j < m; j++) {
                    newCenters[k][j] /= count[k];
                }
            }
        }

        centers = newCenters;
        if (!changed) break;
    }

    return labels;
}

int main() {
    int n, m;
    cout << "Enter number of points: ";
    cin >> n;

    cout << "Enter number of dimensions: ";
    cin >> m;

    vector<vector<double>> data(n, vector<double>(m));

    cout << "Enter points:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> data[i][j];
        }
    }

    int K;
    cout << "Enter K (clusters): ";
    cin >> K;

    vector<int> labels = kmeans(data, K);

    cout << "\nResult:\n";
    for (int i = 0; i < n; i++) {
        cout << "Point " << i << " -> cluster " << labels[i] << "\n";
    }

    return 0;
}
