#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Data {
    string weather;
    string play; // "Yes" or "No"
};

int main() {
    // Training data (easy task)
    vector<Data> arr = {
        {"Sunny", "No"},
        {"Sunny", "No"},
        {"Rain",  "Yes"},
        {"Rain",  "Yes"},
        {"Rain",  "Yes"}
    };

    // Model storage (using only operator[] access)
    unordered_map<string, int> classCount; // classCount["Yes"], classCount["No"]
    unordered_map<string, unordered_map<string, int>> weatherCount; 
    // weatherCount["Sunny"]["Yes"], weatherCount["Sunny"]["No"], etc.

    // ---- TRAIN ----
    for (int i = 0; i < (int)arr.size(); i++) {
        classCount[arr[i].play]++;                 // prior
        weatherCount[arr[i].weather][arr[i].play]++; // likelihood count
    }

    // Make sure keys exist (so classCount["Yes"] works even if absent)
    classCount["Yes"] += 0;
    classCount["No"]  += 0;

    int total = (int)arr.size();

    // ---- TEST SAMPLE ----
    string xtWeather = "Sunny";

    // ---- PREDICT (Naive Bayes) ----
    // score(class) = P(class) * P(weather | class)
    // P(class) = classCount[class] / total
    // P(weather | class) = weatherCount[weather][class] / classCount[class]

    double scoreYes = 0.0;
    double scoreNo  = 0.0;

    double pYes = 0.0, pNo = 0.0;
    if (total > 0) {
        pYes = (double)classCount["Yes"] / total;
        pNo  = (double)classCount["No"]  / total;
    }

    double pWeatherYes = 0.0;
    double pWeatherNo  = 0.0;

    if (classCount["Yes"] > 0) {
        pWeatherYes = (double)weatherCount[xtWeather]["Yes"] / classCount["Yes"];
    }
    if (classCount["No"] > 0) {
        pWeatherNo = (double)weatherCount[xtWeather]["No"] / classCount["No"];
    }

    scoreYes = pYes * pWeatherYes;
    scoreNo  = pNo  * pWeatherNo;

    string predicted = (scoreYes > scoreNo) ? "Yes" : "No";

    cout << "Test: Weather = " << xtWeather << "\n";
    cout << "Predicted Play = " << predicted << "\n";

    return 0;
}
