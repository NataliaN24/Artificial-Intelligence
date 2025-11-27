Implement Tournament Selection (size k).

You are given a vector fitness where:
fitness[i] = fitness of individual i.

Randomly pick k different individuals from the population.

From these k individuals, find the one with the highest fitness.

Return the index of that individual.
  #include<iostream>
#include<vector>
#include<queue>
#include <cmath>
#include <algorithm>
using namespace std;

int tournamentSelect(const vector<int>& fitness, int k)
{
    vector<int>choosenIndexes;
    while (choosenIndexes.size() < k)
    {
        int number = rand() % fitness.size();
        bool inArray = false;

        for (int x : choosenIndexes)
        {
            if (x == number) {
                inArray = true;
                break;
            }
        }

        if (!inArray)
        {
            choosenIndexes.push_back(number);
        }
    }
    int bestIndex = choosenIndexes[0];
    for (int i = 1; i < choosenIndexes.size(); i++)
    {
        if (fitness[choosenIndexes[i]] > fitness[bestIndex])
        {
            bestIndex = choosenIndexes[i];
        }
    }
    return bestIndex;


}
int main()
{
    srand(time(0)); // make random different each run

    int n, k;
    cin >> n >> k;  // n = population size, k = tournament size

    vector<int> fitness(n);
    for (int i = 0; i < n; i++)
        cin >> fitness[i];

    int selected = tournamentSelect(fitness, k);
    cout << selected;

    return 0;
}
