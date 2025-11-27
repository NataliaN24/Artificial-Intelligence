Count the number of 1s (Binary Fitness)

Description:
You are given a chromosome represented as a binary string (or vector of ints 0/1).
Implement the fitness function:

int fitness(const vector<int>& chrom)


Fitness = number of 1s in the chromosome.

Example input:
chrom = {1,0,1,1,0,0,1}
Expected fitness: 4
  #include<iostream>
#include<vector>
#include<queue>
using namespace std;

int fitness(const vector<int>& chrom)
{
    int count = 0;
    for (int i = 0; i < chrom.size(); i++)
    {
        if (chrom[i] == 1)
        {
            count++;
        }
    }
    return count;
}


int main()
{
    
    int n;
    cin >> n;
    vector<int> chromosome(n);
    for (int i = 0; i < n; i++)
    {
        cin >> chromosome[i];
    }
    cout << fitness(chromosome);
    
}
