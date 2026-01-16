#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

double sigmoid(double z)
{
    return 1.0 / (1.0 + exp(-z));
}

double neuronOutput(const vector<double>& x,
                    const vector<double>& w,
                    double bias)
{
    double z = 0.0;
    for (int i = 0; i < (int)x.size(); i++)
    {
        z += x[i] * w[i];
    }
    z += bias;
    return sigmoid(z);
}

int main()
{
    int n;
    cin >> n;                  // 1️⃣ read size

    vector<double> x(n), w(n); // 2️⃣ resize vectors

    for (int i = 0; i < n; i++)
        cin >> x[i];           // 3️⃣ read inputs

    for (int i = 0; i < n; i++)
        cin >> w[i];           // 4️⃣ read weights

    double bias;
    cin >> bias;               // 5️⃣ read bias

    double result = neuronOutput(x, w, bias);

    cout << fixed << setprecision(6);
    cout << result << endl;    // 8️⃣ output

    return 0;
}
