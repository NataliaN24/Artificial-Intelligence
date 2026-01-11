#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    double x;
    double y;
    string label;
};

struct Neighbor {
    double dist;
    string label;
};

double euclideanDist(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

bool compareNeighbor(const Neighbor& a, const Neighbor& b) {
    return a.dist < b.dist;
}

vector<Neighbor> buildNeighbors(const vector<Point>& points, double newX, double newY) {
    vector<Neighbor> neighbors;
    neighbors.reserve(points.size());

    for (int i = 0; i < (int)points.size(); ++i) {
        Neighbor n;
        n.dist = euclideanDist(points[i].x, points[i].y, newX, newY);
        n.label = points[i].label;
        neighbors.push_back(n);
    }
    return neighbors;
}

int findLabelIndex(const vector<string>& labels, const string& label) {
    for (int i = 0; i < (int)labels.size(); i++) {
        if (labels[i] == label) return i;
    }
    return -1;
}

string knn(vector<Neighbor>& narr, int k) {
    if (narr.empty()) return "ERROR_EMPTY_DATA";
    if (k <= 0) return "ERROR_INVALID_K";
    if (k > (int)narr.size()) k = (int)narr.size();

    sort(narr.begin(), narr.end(), compareNeighbor);

    vector<string> labels;
    vector<int> counts;
    vector<double> closestDist;

    for (int i = 0; i < k; i++) {
        int index = findLabelIndex(labels, narr[i].label);

        if (index == -1) {
            labels.push_back(narr[i].label);
            counts.push_back(1);
            closestDist.push_back(narr[i].dist);
        }
        else {
            counts[index]++;
            if (narr[i].dist < closestDist[index]) {
                closestDist[index] = narr[i].dist;
            }
        }
    }

    string bestLabel = labels[0];
    int bestCount = counts[0];
    double bestDistance = closestDist[0];

    for (int i = 1; i < (int)labels.size(); i++) {
        if (counts[i] > bestCount ||
            (counts[i] == bestCount && closestDist[i] < bestDistance)) {
            bestCount = counts[i];
            bestDistance = closestDist[i];
            bestLabel = labels[i];
        }
    }

    return bestLabel;
}

int main() {
    int num;
    cin >> num;

    vector<Point> arr;
    arr.reserve(num);

    for (int i = 0; i < num; i++) {
        Point p;
        cin >> p.x >> p.y >> p.label;
        arr.push_back(p);
    }

    int k;
    cin >> k;

    double newX, newY;
    cin >> newX >> newY;

    vector<Neighbor> neighbors = buildNeighbors(arr, newX, newY);
    cout << knn(neighbors, k) << "\n";

    return 0;
}

