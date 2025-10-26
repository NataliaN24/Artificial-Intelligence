#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

// Objective function (the "hill" to climb)
double objective(double x) {
    // Example: peak at x = 3, max value = 9
    return -(x - 3) * (x - 3) + 9;
}

// Hill Climbing algorithm
double hillClimb(double start, double stepSize, int maxIterations) {
    double current = start;
    double currentVal = objective(current);

    for (int i = 0; i < maxIterations; i++) {
        // Generate two neighbors: left and right
        double next1 = current + stepSize;
        double next2 = current - stepSize;

        double val1 = objective(next1);
        double val2 = objective(next2);

        // Find the best neighbor
        double bestNeighbor = current;
        double bestValue = currentVal;

        if (val1 > bestValue) {
            bestNeighbor = next1;
            bestValue = val1;
        }
        if (val2 > bestValue) {
            bestNeighbor = next2;
            bestValue = val2;
        }

        // If no improvement, stop
        if (bestValue <= currentVal) {
            cout << "Local maximum reached at iteration " << i << endl;
            break;
        }

        // Move to the better neighbor
        current = bestNeighbor;
        currentVal = bestValue;

        cout << "Iteration " << i + 1 << ": x = " << current
             << ", f(x) = " << currentVal << endl;
    }

    return current;
}

int main() {
    srand(time(0));

    double start = (rand() % 1000) / 100.0; // random start between 0 and 10
    double stepSize = 0.1;
    int maxIterations = 100;

    cout << "Starting at x = " << start << endl;
    double result = hillClimb(start, stepSize, maxIterations);

    cout << "\nBest solution found: x = " << result
         << ", f(x) = " << objective(result) << endl;

    return 0;
}
