In the Knapsack Problem, you have:

a list of items

each item has a weight

each item has a value

you have a knapsack capacity (max weight allowed)

Your goal is to select items with the maximum value, but not exceed capacity.
  Your job is to compute:

1️⃣ Total weight of selected items
2️⃣ Total value of selected items
3️⃣ If weight > capacity → return 0
4️⃣ Else → return total value

This evaluates how good a solution is.

  #include<iostream>
#include<vector>
#include<queue>
using namespace std;

int fitness(const vector<int>& chrom,
    const vector<int>& weights,
    const vector<int>& values,
    int capacity)
{
    int totalWeight = 0;
    int totalVal = 0;
    for (int i = 0; i < chrom.size(); ++i)
    {
        if (chrom[i] == 1)
        {
            totalWeight += weights[i];
            totalVal += values[i];
        }
    }
    if (totalWeight <= capacity)
    {
        return totalVal;
    }
    else
    {
        return 0;
    }
}

int main()
{
    
    int n;
    cin >> n;
    vector<int> chromosome(n);
    vector<int> weights(n);
    vector<int> values(n);
    int cap;
    cin >> cap;
    for (int i = 0; i < n; i++)
    {
        cin >> chromosome[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> weights[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> values[i];
    }
    cout << fitness(chromosome, weights, values, cap);
    
}
