
int rouletteSelect(const vector<int>& fitness);
Where fitness[i] is the fitness of individual i.
Return the index of the selected individual.

Input example:
fitness = {4, 1, 5}
Total = 10
Probabilities = 0.4, 0.1, 0.5

Output: random index, but 2 is most likely.

#include<iostream>
#include<vector>
#include<queue>
#include <cmath>
using namespace std;

int rouletteSelect(const vector<int>& fitness)
{
    int total = 0;
    vector<double>allProbabilities(fitness.size());
    for (int i = 0; i < fitness.size(); i++)
    {
        total += fitness[i];
    }
    for (int i = 0; i < fitness.size(); i++)
    {
        allProbabilities[i] = (double)fitness[i] / total;
    }
    vector<double>cumulative(fitness.size());
    cumulative[0] = allProbabilities[0];
    for (int i = 1; i < allProbabilities.size(); i++)
    {
        cumulative[i] = allProbabilities[i] + cumulative[i - 1];

    }
    double randomNumber = (double)rand() / RAND_MAX;
    //find in which interval falls into

    for (int i = 0; i < cumulative.size(); i++)
    {
        if (randomNumber <= cumulative[i])
        {
            return i;
        }
            
    }
    return fitness.size() - 1;
}

int main() {
    srand(time(0));

    int n;
    cin >> n;

    vector<int> fitness(n);
    for (int i = 0; i < n; i++)
        cin >> fitness[i];

    int selected = rouletteSelect(fitness);
    cout << selected;
}
