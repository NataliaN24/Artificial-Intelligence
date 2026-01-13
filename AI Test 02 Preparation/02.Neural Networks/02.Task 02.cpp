#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

int main()
{
    cout << fixed << setprecision(6);

    cout << "sigmoid(-2) = " << sigmoid(-2) << endl;
    cout << "sigmoid(0)  = " << sigmoid(0) << endl;
    cout << "sigmoid(2)  = " << sigmoid(2) << endl;

    return 0;
}
