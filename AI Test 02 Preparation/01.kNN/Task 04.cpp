#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

struct Point {
    double x1;
    double x2;
    string label;
};

struct Neighbor {
    double dist;
    string label;
};

struct MinMax {
    double min1, max1;
    double min2, max2;
};

double getDist(double x1, double newX1, double x2, double newX2) {
    double dx1 = x1 - newX1;
    double dx2 = x2 - newX2;
    return sqrt(dx1 * dx1 + dx2 * dx2);
}

bool compareNeighbor(const Neighbor& a, const Neighbor& b) {
    return a.dist < b.dist;
}

MinMax computeMinMax(const vector<Point>& points) {
    MinMax mm;
    mm.min1 = mm.max1 = points[0].x1;
    mm.min2 = mm.max2 = points[0].x2;

    for (int i = 1; i < (int)points.size(); i++) {
        mm.min1 = min(mm.min1, points[i].x1);
        mm.max1 = max(mm.max1, points[i].x1);

        mm.min2 = min(mm.min2, points[i].x2);
        mm.max2 = max(mm.max2, points[i].x2);
    }
    return mm;
}

double minMaxNormalize(double v, double vmin, double vmax) {
    double range = vmax - vmin;
    if (range == 0.0) return 0.0; // if all values same, collapse to 0
    return (v - vmin) / range;
}

string knnMinMax(const vector<Point>& points, double newX1, double newX2, int k) {
    if (points.empty()) return "ERROR_EMPTY";
    if (k <= 0) return "ERROR_K";
    if (k > (int)points.size()) k = (int)points.size();

    // 1) min/max from TRAINING ONLY
    MinMax mm = computeMinMax(points);

    // 2) normalize test point
    double tx1 = minMaxNormalize(newX1, mm.min1, mm.max1);
    double tx2 = minMaxNormalize(newX2, mm.min2, mm.max2);

    // 3) build neighbors with distances in normalized space
    vector<Neighbor> neigh;
    neigh.reserve(points.size());

    for (int i = 0; i < (int)points.size(); i++) {
        double px1 = minMaxNormalize(points[i].x1, mm.min1, mm.max1);
        double px2 = minMaxNormalize(points[i].x2, mm.min2, mm.max2);

        Neighbor nb;
        nb.dist = getDist(px1, tx1, px2, tx2);
        nb.label = points[i].label;
        neigh.push_back(nb);
    }

    // 4) sort by distance
    sort(neigh.begin(), neigh.end(), compareNeighbor);

    // 5) majority vote using vectors (simple, no maps)
    vector<string> labels;
    vector<int> counts;
    vector<double> closest;

    for (int i = 0; i < k; i++) {
        // find label index
        int idx = -1;
        for (int j = 0; j < (int)labels.size(); j++) {
            if (labels[j] == neigh[i].label) {
                idx = j;
                break;
            }
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

    // choose best label (tie -> closest wins)
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

int main() {
    int n;
    cin >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x1 >> points[i].x2 >> points[i].label;
    }

    double newX1, newX2;
    int k;
    cin >> newX1 >> newX2 >> k;

    cout << knnMinMax(points, newX1, newX2, k) << "\n";
    return 0;
}
