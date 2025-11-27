🎯 TASK: Elitism Selection (Return Top k Individuals)
Requirement (simple):

Given a population with their fitness values,
select the k individuals with the highest fitness
and return their indices.

Function signature:
vector<int> elitismSelect(const vector<int>& fitness, int k);

What to do:

Look at all fitness values

Find the top k largest fitness entries

Return their indices in decreasing order of fitness

#include <iostream>
#include <vector>
using namespace std;

vector<int> elitismSelect(const vector<int>& fitness, int k)
{
    int n = fitness.size();

    // Make an index vector: {0,1,2,3,...}
    vector<int> idx(n);
    for (int i = 0; i < n; i++)
        idx[i] = i;

    // Bubble sort indices based on fitness (descending)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (fitness[idx[j]] < fitness[idx[j + 1]])
            {
                int temp = idx[j];
                idx[j] = idx[j + 1];
                idx[j + 1] = temp;
            }
        }
    }

    // Take top k indices
    vector<int> result;
    for (int i = 0; i < k; i++)
        result.push_back(idx[i]);

    return result;
}

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> fitness(n);
    for (int i = 0; i < n; i++)
        cin >> fitness[i];

    vector<int> elite = elitismSelect(fitness, k);

    for (int x : elite)
        cout << x << " ";

    return 0;
}
