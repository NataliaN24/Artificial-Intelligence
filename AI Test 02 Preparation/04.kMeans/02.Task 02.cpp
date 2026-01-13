#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

vector<int> assignLabels(const vector<double>& arr, double c1, double c2) {
    vector<int> labels(arr.size(), -1);
    for (int i = 0; i < (int)arr.size(); i++) {
        double d1 = fabs(arr[i] - c1);
        double d2 = fabs(arr[i] - c2);
        labels[i] = (d1 <= d2) ? 0 : 1;
    }
    return labels;
}

void updateCenters(const vector<double>& arr, const vector<int>& labels,
                   double& c1, double& c2) {
    double sum1 = 0.0, sum2 = 0.0;
    int cnt1 = 0, cnt2 = 0;

    for (int i = 0; i < (int)arr.size(); i++) {
        if (labels[i] == 0) { sum1 += arr[i]; cnt1++; }
        else               { sum2 += arr[i]; cnt2++; }
    }

    if (cnt1 > 0) c1 = sum1 / cnt1;
    if (cnt2 > 0) c2 = sum2 / cnt2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;

    vector<double> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    // init: min and max
    double c1 = *min_element(arr.begin(), arr.end());
    double c2 = *max_element(arr.begin(), arr.end());

    vector<int> labels(n, -1);

    for (int iter = 0; iter < t; iter++) {
        vector<int> newLabels = assignLabels(arr, c1, c2);

        if (newLabels == labels) break; // converged
        labels = newLabels;

        updateCenters(arr, labels, c1, c2);
    }

    cout << fixed << setprecision(6);
    cout << "Center 0: " << c1 << "\n";
    cout << "Center 1: " << c2 << "\n";

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " -> " << labels[i] << "\n";
    }

    return 0;
}
