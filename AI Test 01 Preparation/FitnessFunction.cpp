You are given:

A list of items, where each item has:

weight

value

A chromosome represented as a vector of 0/1, where:

1 means the item is selected

0 means it is not selected

A maximum weight limit of the knapsack.

Your task:

Write a function:
int fitness(const vector<int>& chromosome,
            const vector<int>& weights,
            const vector<int>& values,
            int maxWeight)

The fitness function should:

Calculate total weight and total value of the selected items.

If total weight exceeds maxWeight, return 0 (invalid solution).

Otherwise return the total value (this is the fitness score).

✔️ Example Input
weights = [3, 4, 7, 8]
values  = [5, 6, 10, 13]
chromosome = [1, 0, 1, 0]
maxWeight = 10

Explanation:

Selected items:

Item 0 → weight 3, value 5

Item 2 → weight 7, value 10

Total weight = 3 + 7 = 10
Total value = 5 + 10 = 15

Because total weight ≤ 10 → fitness = 15

✔️ Expected Output:
15
Crossover Function – Requirements

You must create a function:

vector<int> crossover(const vector<int>& parent1,
                      const vector<int>& parent2)

Crossover Requirements

Crossover point:

Randomly choose an index cp in the range
1 to chromosome_length - 2
(to avoid trivial copies)

Create child chromosome:

Genes before the crossover point come from parent1

Genes after the crossover point come from parent2

Return the resulting child chromosome

Example:
parent1: 1 0 1 1 0 1
parent2: 0 1 1 0 1 0
cp = 3
child:   1 0 1 | 0 1 0

3️⃣ Mutation Function – Requirements

You must create a function:

void mutate(vector<int>& chromosome, double mutationRate)

Mutation Requirements

For each gene in the chromosome:



If gene == 0 → change to 1

If gene == 1 → change to 0


Before: 0 1 1 0 1
After:  0 0 1 1 1   (bit 1 flipped at index 1)

///////////////////////////////////////////////
#include<iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;


int fitness(const vector<int>& chromosome,
    const vector<int>& weights,
    const vector<int>& values,
    int maxWeight)
{
    int totalWeight = 0;
    int totalValue = 0;
    for (int i = 0; i < weights.size(); ++i)
    {
        if (chromosome[i] == 1)
        {
            totalWeight += weights[i];
            totalValue += values[i];
        }
    }
    if (totalWeight > maxWeight)
    {
        return 0;
    }
    else
    {
        return totalValue;
    }

}
vector<int> crossover(const vector<int>& parent1,
    const vector<int>& parent2)
{
    vector<int> child;
    if (parent1.size() != parent2.size())
    {
        return {};
    }
      int divisionIndex = parent1.size() / 2 ;
        for (int i = 0; i < divisionIndex; i++)
        {
            child.push_back(parent1[i]);
        }
        for (int i = divisionIndex; i < parent2.size(); i++)
        {
            child.push_back(parent2[i]);
        }
        return child;
}
void mutate(vector<int>& chromosome,int index)
{
    if (chromosome[index] == 1)
    {
        chromosome[index] = 0;
    }
    else if (chromosome[index] == 0)
    {
        chromosome[index] = 1;
    }
}


int main()
{
    vector<int> weights = { 2, 3, 4, 5 };
    vector<int> values = { 3, 4, 5, 6 };
    int maxWeight = 7;

    vector<int> parent1 = { 1, 0, 1, 0 };
    vector<int> parent2 = { 0, 1, 0, 1 };

    int fit1 = fitness(parent1, weights, values, maxWeight);
    int fit2 = fitness(parent2, weights, values, maxWeight);

    vector<int> child = crossover(parent1, parent2);

    mutate(child, 2);

    cout << "Fitness 1: " << fit1 << endl;
    cout << "Fitness 2: " << fit2 << endl;

    cout << "Child after mutation: ";
    for (int x : child) cout << x << " ";
    cout << endl;

    return 0;
}
