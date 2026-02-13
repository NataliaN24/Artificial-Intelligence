#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>
#include <map>
#include <iomanip>
#include <limits>

using namespace std;

struct DataPoint {
    vector<double> features;
    int label;
};

struct NormalizationParams {
    vector<double> minValues;
    vector<double> maxValues;
};

vector<DataPoint> loadIrisDataset(const string& filename) {
    vector<DataPoint> dataset;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return dataset;
    }

    string line;
    
    map<string, int> classMap;
    classMap["Iris-setosa"] = 0;
    classMap["Iris-versicolor"] = 1;
    classMap["Iris-virginica"] = 2;

    while (getline(file, line)) {
       
        if (line.empty()) continue;

        DataPoint point;
        stringstream ss(line);
        string value;

        for (int i = 0; i < 4; i++) {
            getline(ss, value, ',');
            point.features.push_back(stod(value));
        }

        getline(ss, value, ',');
       
        value.erase(remove(value.begin(), value.end(), '\r'), value.end());
        value.erase(remove(value.begin(), value.end(), ' '), value.end());

        if (classMap.find(value) != classMap.end()) {
            point.label = classMap[value];
        }
        else {
         
            point.label = stoi(value);
        }

        dataset.push_back(point);
    }

    file.close();
    return dataset;
}

NormalizationParams calculateNormalizationParams(const vector<DataPoint>& data) {
    NormalizationParams params;

    if (data.empty()) return params;

    int numFeatures = data[0].features.size();

    params.minValues.resize(numFeatures, numeric_limits<double>::max());
    params.maxValues.resize(numFeatures, numeric_limits<double>::lowest());

    for (const auto& point : data) {
        for (int i = 0; i < numFeatures; i++) {
            if (point.features[i] < params.minValues[i]) {
                params.minValues[i] = point.features[i];
            }
            if (point.features[i] > params.maxValues[i]) {
                params.maxValues[i] = point.features[i];
            }
        }
    }

    return params;
}

void normalizeData(vector<DataPoint>& data, const NormalizationParams& params) {
    for (auto& point : data) {
        for (size_t i = 0; i < point.features.size(); i++) {
            double range = params.maxValues[i] - params.minValues[i];
            if (range > 0) {
                point.features[i] = (point.features[i] - params.minValues[i]) / range;
            }
            else {
                point.features[i] = 0; 
            }
        }
    }
}

void stratifiedSplit(const vector<DataPoint>& data,
    vector<DataPoint>& trainSet,
    vector<DataPoint>& testSet,
    double trainRatio,
    unsigned int seed) {

    map<int, vector<DataPoint>> byClass;
    for (const auto& point : data) {
        byClass[point.label].push_back(point);
    }

    mt19937 rng(seed);

    for (auto& pair : byClass) {
        vector<DataPoint>& classData = pair.second;

        shuffle(classData.begin(), classData.end(), rng);

        int trainCount = static_cast<int>(classData.size() * trainRatio);

        for (int i = 0; i < trainCount; i++) {
            trainSet.push_back(classData[i]);
        }

        for (size_t i = trainCount; i < classData.size(); i++) {
            testSet.push_back(classData[i]);
        }
    }

    shuffle(trainSet.begin(), trainSet.end(), rng);
    shuffle(testSet.begin(), testSet.end(), rng);
}

double euclideanDistance(const vector<double>& a, const vector<double>& b) {
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); i++) {
        double diff = a[i] - b[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

int knnPredict(const DataPoint& testPoint,
    const vector<DataPoint>& trainSet,
    int k) {

    vector<pair<double, int>> distances;

    for (const auto& trainPoint : trainSet) {
        double dist = euclideanDistance(testPoint.features, trainPoint.features);
        distances.push_back({ dist, trainPoint.label });
    }

    sort(distances.begin(), distances.end(),
        [](const pair<double, int>& a, const pair<double, int>& b) {
            return a.first < b.first;
        });

    map<int, int> votes;
    for (int i = 0; i < k && i < static_cast<int>(distances.size()); i++) {
        votes[distances[i].second]++;
    }

    int predictedClass = -1;
    int maxVotes = 0;
    for (const auto& vote : votes) {
        if (vote.second > maxVotes) {
            maxVotes = vote.second;
            predictedClass = vote.first;
        }
    }

    return predictedClass;
}

double calculateAccuracy(const vector<DataPoint>& testSet,
    const vector<DataPoint>& trainSet,
    int k) {
    int correct = 0;

    for (const auto& testPoint : testSet) {
        int predicted = knnPredict(testPoint, trainSet, k);
        if (predicted == testPoint.label) {
            correct++;
        }
    }

    return (static_cast<double>(correct) / testSet.size()) * 100.0;
}

void tenFoldCrossValidation(const vector<DataPoint>& data,
    int k,
    vector<double>& foldAccuracies,
    double& avgAccuracy,
    double& stdDev) {

    int numFolds = 10;
    foldAccuracies.clear();

    map<int, vector<DataPoint>> byClass;
    for (const auto& p : data) {
        byClass[p.label].push_back(p);
    }

    mt19937 rng(42);

    for (auto& pair : byClass) {
        shuffle(pair.second.begin(), pair.second.end(), rng);
    }

    vector<vector<DataPoint>> folds(numFolds);

    for (const auto& pair : byClass) {
        const vector<DataPoint>& classData = pair.second;
        int foldSize = classData.size() / numFolds;

        for (int i = 0; i < numFolds; i++) {
            int start = i * foldSize;
            int end = (i == numFolds - 1) ? classData.size() : start + foldSize;

            for (int j = start; j < end; j++) {
                folds[i].push_back(classData[j]);
            }
        }
    }

    for (int i = 0; i < numFolds; i++) {
        vector<DataPoint> testFold = folds[i];
        vector<DataPoint> trainFold;

        for (int j = 0; j < numFolds; j++) {
            if (j != i) {
                trainFold.insert(trainFold.end(), folds[j].begin(), folds[j].end());
            }
        }

        NormalizationParams params = calculateNormalizationParams(trainFold);
        normalizeData(trainFold, params);
        normalizeData(testFold, params);

        double accuracy = calculateAccuracy(testFold, trainFold, k);
        foldAccuracies.push_back(accuracy);
    }

    avgAccuracy = 0.0;
    for (double acc : foldAccuracies) {
        avgAccuracy += acc;
    }
    avgAccuracy /= numFolds;

    double sumSq = 0.0;
    for (double acc : foldAccuracies) {
        double diff = acc - avgAccuracy;
        sumSq += diff * diff;
    }
    stdDev = sqrt(sumSq / numFolds);
}


int main() {
   
    string filename = "iris.data";
    vector<DataPoint> dataset = loadIrisDataset(filename);

    if (dataset.empty()) {
        cerr << "Failed to load dataset. Please ensure 'iris.data' is in the current directory." << endl;
        cerr << "Download from: https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data" << endl;
        return 1;
    }

    cout << "Loaded " << dataset.size() << " samples from Iris dataset." << endl;
    cout << endl;

    int k;
    cout << "Enter the value of k: ";
    cin >> k;
    cout << endl;

    if (k <= 0) {
        cerr << "Error: k must be positive." << endl;
        return 1;
    }

    vector<DataPoint> dataCopy = dataset;

    vector<DataPoint> trainSet, testSet;
    stratifiedSplit(dataCopy, trainSet, testSet, 0.8, 42);

    cout << "Data split: " << trainSet.size() << " training, "
        << testSet.size() << " test samples." << endl;
    cout << endl;

    NormalizationParams normParams = calculateNormalizationParams(trainSet);

    normalizeData(trainSet, normParams);
    normalizeData(testSet, normParams);

    double trainAccuracy = calculateAccuracy(trainSet, trainSet, k);

    cout << "1. Train Set Accuracy:" << endl;
    cout << "   Accuracy: " << fixed << setprecision(2) << trainAccuracy << "%" << endl;
    cout << endl;

    vector<double> foldAccuracies;
    double avgAccuracy, stdDev;

    vector<DataPoint> trainSetOriginal;
    vector<DataPoint> testSetOriginal;
    stratifiedSplit(dataset, trainSetOriginal, testSetOriginal, 0.8, 42);

    tenFoldCrossValidation(trainSetOriginal, k, foldAccuracies, avgAccuracy, stdDev);

    cout << "2. 10-Fold Cross-Validation Results:" << endl;
    cout << endl;

    for (int i = 0; i < 10; i++) {
        cout << "   Accuracy Fold " << (i + 1) << ": "
            << fixed << setprecision(2) << foldAccuracies[i] << "%" << endl;
    }

    cout << endl;
    cout << "   Average Accuracy: " << fixed << setprecision(2) << avgAccuracy << "%" << endl;
    cout << "   Standard Deviation: " << fixed << setprecision(2) << stdDev << "%" << endl;
    cout << endl;

    double testAccuracy = calculateAccuracy(testSet, trainSet, k);

    cout << "3. Test Set Accuracy:" << endl;
    cout << "   Accuracy: " << fixed << setprecision(2) << testAccuracy << "%" << endl;

    return 0;
}