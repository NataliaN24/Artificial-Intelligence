#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <iomanip>

using namespace std;

/* ---------- MSE ---------- */
double mse(const vector<double>& y, const vector<double>& y_hat)
{
    double sum = 0.0;
    for (int i = 0; i < (int)y.size(); i++)
    {
        double diff = y[i] - y_hat[i];
        sum += diff * diff;
    }
    return sum / y.size();
}

/* ---------- Linear model (underfitting) ---------- */
double linearPredict(double x)
{
    double w = 2.0;
    double b = -3.0;
    return w * x + b;
}

/* ---------- Memorization model (overfitting) ---------- */
double memorizationPredict(double x,
                           const unordered_map<double, double>& memory)
{
    if (memory.count(x))
        return memory.at(x);
    return 0.0;
}

/* ---------- Diagnosis ---------- */
string diagnose(double trainError, double testError)
{
    if (trainError > 1.0 && testError > 1.0)
        return "UNDERFITTING";

    if (trainError < 1e-6 && testError > 1.0)
        return "OVERFITTING";

    return "GOOD FIT";
}

int main()
{
    cout << fixed << setprecision(4);

    vector<double> x_train = {1, 2, 3, 4};
    vector<double> y_train = {1, 4, 9, 16};

    vector<double> x_test = {5};
    vector<double> y_test = {25};

    /* ---------- UNDERFITTING ---------- */
    vector<double> y_hat_train_linear;
    vector<double> y_hat_test_linear;

    for (double x : x_train)
        y_hat_train_linear.push_back(linearPredict(x));

    for (double x : x_test)
        y_hat_test_linear.push_back(linearPredict(x));

    double trainErrLinear = mse(y_train, y_hat_train_linear);
    double testErrLinear = mse(y_test, y_hat_test_linear);

    cout << "Linear model:\n";
    cout << "Train MSE = " << trainErrLinear << "\n";
    cout << "Test  MSE = " << testErrLinear << "\n";
    cout << diagnose(trainErrLinear, testErrLinear) << "\n\n";

    /* ---------- OVERFITTING ---------- */
    unordered_map<double, double> memory;
    for (int i = 0; i < (int)x_train.size(); i++)
        memory[x_train[i]] = y_train[i];

    vector<double> y_hat_train_mem;
    vector<double> y_hat_test_mem;

    for (double x : x_train)
        y_hat_train_mem.push_back(memorizationPredict(x, memory));

    for (double x : x_test)
        y_hat_test_mem.push_back(memorizationPredict(x, memory));

    double trainErrMem = mse(y_train, y_hat_train_mem);
    double testErrMem = mse(y_test, y_hat_test_mem);

    cout << "Memorization model:\n";
    cout << "Train MSE = " << trainErrMem << "\n";
    cout << "Test  MSE = " << testErrMem << "\n";
    cout << diagnose(trainErrMem, testErrMem) << "\n";

    return 0;
}
