#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

double mse(const vector<double>& y, const vector<double>& y_hat)
{
    double sum = 0.0;
    int n = y.size();

    for (int i = 0; i < n; i++)
    {
        double diff = y[i] - y_hat[i];
        sum += diff * diff;
    }

    return sum / n;
}

int main()
{
    vector<double> y     = {1, 0, 1};
    vector<double> y_hat = {0.8, 0.2, 0.6};

    cout << fixed << setprecision(6);
    cout << "MSE = " << mse(y, y_hat) << endl;

    return 0;
}
