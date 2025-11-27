Bit-Flip Mutation (Binary Chromosome)

This is the most common mutation task for genetic algorithms.

📌 TASK REQUIREMENT

You are given a binary chromosome:

chrom = {1, 0, 1, 1, 0, 0, 1}


and a mutation index:

mutationIndex = 3

👉 Your task:

Implement a function that flips the bit at mutationIndex:

if chrom[i] = 1 → change it to 0

if chrom[i] = 0 → change it to 1
  void bitFlipMutation(vector<int>& chrom, int index)
{
    if (chrom[index] == 1)
    {
        chrom[index] = 0;
    }
    else if (chrom[index] == 0)
    {
        chrom[index] = 1;
    }
}
