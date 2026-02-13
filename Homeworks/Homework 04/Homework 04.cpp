#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

struct Item {
    int weight;
    int value;
    double ratio;
};

class Individual {
public:
    vector<bool> chromosome;
    int fitness;
    int totalWeight;
    int totalValue;
    bool needsFitnessUpdate;

    Individual(int n) : chromosome(n, false), fitness(0), totalWeight(0), totalValue(0), needsFitnessUpdate(true) {}

    void calculateFitness(const vector<Item>& items, int capacity) {
        if (!needsFitnessUpdate && totalWeight <= capacity) return;

        totalWeight = 0;
        totalValue = 0;

        for (int i = 0; i < chromosome.size(); i++) {
            if (chromosome[i]) {
                totalWeight += items[i].weight;
                totalValue += items[i].value;
            }
        }

        if (totalWeight > capacity) {
            fitness = totalValue - (totalWeight - capacity) * 10000;
        }
        else {
            fitness = totalValue;
        }
        needsFitnessUpdate = false;
    }


    void fastRepair(const vector<Item>& items, int capacity, const vector<int>& sortedIndices) {
        if (totalWeight <= capacity) {
            needsFitnessUpdate = false;
            return;
        }


        for (int idx : sortedIndices) {
            if (totalWeight <= capacity) break;
            if (chromosome[idx]) {
                chromosome[idx] = false;
                totalWeight -= items[idx].weight;
                totalValue -= items[idx].value;
            }
        }

        fitness = totalValue;
        needsFitnessUpdate = false;
    }
};

class GeneticAlgorithm {
private:
    int capacity;
    int numItems;
    vector<Item> items;
    vector<Individual> population;
    vector<int> sortedIndices;
    int populationSize;
    int maxGenerations;
    double crossoverRate;
    double mutationRate;
    mt19937 rng;
    vector<int> outputGenerations;

public:
    GeneticAlgorithm(int cap, int n, const vector<Item>& itms, int popSize = 100, int maxGen = 1000)
        : capacity(cap), numItems(n), items(itms), populationSize(popSize),
        maxGenerations(maxGen), crossoverRate(0.85), mutationRate(0.015),
        rng(time(nullptr)) {


        for (int i = 0; i < numItems; i++) {
            items[i].ratio = (double)items[i].value / items[i].weight;
        }

        sortedIndices.resize(numItems);
        for (int i = 0; i < numItems; i++) {
            sortedIndices[i] = i;
        }
        sort(sortedIndices.begin(), sortedIndices.end(),
            [&](int a, int b) { return items[a].ratio < items[b].ratio; });


        outputGenerations.push_back(1);
        if (maxGenerations > 2) {
            int intermediateCount = 8;
            int step = max(1, (maxGenerations - 2) / (intermediateCount + 1));
            for (int i = 1; i <= intermediateCount; i++) {
                int gen = 1 + i * step;
                if (gen < maxGenerations) {
                    outputGenerations.push_back(gen);
                }
            }
        }
        outputGenerations.push_back(maxGenerations);

        while (outputGenerations.size() < 10 && maxGenerations > outputGenerations.size()) {
            for (int i = 1; i < maxGenerations && outputGenerations.size() < 10; i++) {
                if (find(outputGenerations.begin(), outputGenerations.end(), i) == outputGenerations.end()) {
                    outputGenerations.push_back(i);
                    break;
                }
            }
        }
        sort(outputGenerations.begin(), outputGenerations.end());
    }

    void initializePopulation() {
        population.clear();
        population.reserve(populationSize);
        uniform_real_distribution<double> probDist(0.0, 1.0);


        Individual greedy(numItems);
        int currentWeight = 0;
        vector<pair<double, int>> bestRatios;
        for (int i = 0; i < numItems; i++) {
            bestRatios.push_back({ items[i].ratio, i });
        }
        sort(bestRatios.rbegin(), bestRatios.rend());

        for (auto& p : bestRatios) {
            if (currentWeight + items[p.second].weight <= capacity) {
                greedy.chromosome[p.second] = true;
                currentWeight += items[p.second].weight;
            }
        }
        greedy.calculateFitness(items, capacity);
        population.push_back(greedy);


        double avgRatio = 0;
        for (const auto& item : items) {
            avgRatio += item.ratio;
        }
        avgRatio /= numItems;
        double ratioMultiplier = 1.0 / (avgRatio * 2);

        for (int i = 1; i < populationSize; i++) {
            Individual ind(numItems);

            for (int j = 0; j < numItems; j++) {
                double prob = probDist(rng);
                double threshold = 0.2 + 0.5 * (items[j].ratio * ratioMultiplier);
                ind.chromosome[j] = (prob < threshold);
            }

            ind.calculateFitness(items, capacity);
            ind.fastRepair(items, capacity, sortedIndices);
            population.push_back(ind);
        }
    }

    Individual tournamentSelection(int tournamentSize = 3) {
        uniform_int_distribution<int> dist(0, populationSize - 1);
        int bestIdx = dist(rng);

        for (int i = 1; i < tournamentSize; i++) {
            int candidateIdx = dist(rng);
            if (population[candidateIdx].fitness > population[bestIdx].fitness) {
                bestIdx = candidateIdx;
            }
        }

        return population[bestIdx];
    }

    pair<Individual, Individual> crossover(const Individual& parent1, const Individual& parent2) {
        uniform_real_distribution<double> prob(0.0, 1.0);

        if (prob(rng) > crossoverRate) {
            return { parent1, parent2 };
        }

        Individual child1(numItems);
        Individual child2(numItems);

        uniform_int_distribution<int> pointDist(0, numItems - 1);
        int crossoverPoint = pointDist(rng);


        for (int i = 0; i < crossoverPoint; i++) {
            child1.chromosome[i] = parent1.chromosome[i];
            child2.chromosome[i] = parent2.chromosome[i];
        }
        for (int i = crossoverPoint; i < numItems; i++) {
            child1.chromosome[i] = parent2.chromosome[i];
            child2.chromosome[i] = parent1.chromosome[i];
        }

        child1.needsFitnessUpdate = true;
        child2.needsFitnessUpdate = true;
        child1.calculateFitness(items, capacity);
        child1.fastRepair(items, capacity, sortedIndices);
        child2.calculateFitness(items, capacity);
        child2.fastRepair(items, capacity, sortedIndices);

        return { child1, child2 };
    }

    void mutate(Individual& ind) {
        uniform_real_distribution<double> prob(0.0, 1.0);
        bool changed = false;

        for (int i = 0; i < numItems; i++) {
            if (prob(rng) < mutationRate) {
                ind.chromosome[i] = !ind.chromosome[i];
                changed = true;
            }
        }

        if (changed) {
            ind.needsFitnessUpdate = true;
            ind.calculateFitness(items, capacity);
            ind.fastRepair(items, capacity, sortedIndices);
        }
    }

    void runEvolution() {
        initializePopulation();

        int currentGen = 1;
        int bestOverall = 0;
        int nextOutputIndex = 0;
        int noImprovementCount = 0;
        const int MAX_NO_IMPROVEMENT = min(150, maxGenerations / 3);

        while (currentGen <= maxGenerations) {

            if (currentGen % 5 == 0 ||
                (nextOutputIndex < outputGenerations.size() && outputGenerations[nextOutputIndex] == currentGen)) {
                sort(population.begin(), population.end(),
                    [](const Individual& a, const Individual& b) {
                        return a.fitness > b.fitness;
                    });
            }
            else {
                nth_element(population.begin(), population.begin(), population.end(),
                    [](const Individual& a, const Individual& b) {
                        return a.fitness > b.fitness;
                    });
            }

            int currentBest = population[0].fitness;
            if (currentBest > bestOverall) {
                bestOverall = currentBest;
                noImprovementCount = 0;
            }
            else {
                noImprovementCount++;
            }

            while (nextOutputIndex < outputGenerations.size() &&
                outputGenerations[nextOutputIndex] == currentGen) {
                cout << currentBest << endl;
                nextOutputIndex++;
            }

            if (noImprovementCount > MAX_NO_IMPROVEMENT && currentGen > maxGenerations / 2) {
                while (nextOutputIndex < outputGenerations.size()) {
                    cout << currentBest << endl;
                    nextOutputIndex++;
                }
                break;
            }

            vector<Individual> newPopulation;
            newPopulation.reserve(populationSize);

            int eliteCount = max(1, populationSize / 10);
            for (int i = 0; i < eliteCount; i++) {
                newPopulation.push_back(population[i]);
            }

            while (newPopulation.size() < populationSize) {
                Individual parent1 = tournamentSelection();
                Individual parent2 = tournamentSelection();

                auto children = crossover(parent1, parent2);
                mutate(children.first);
                mutate(children.second);

                newPopulation.push_back(children.first);
                if (newPopulation.size() < populationSize) {
                    newPopulation.push_back(children.second);
                }
            }

            population = move(newPopulation);
            currentGen++;
        }

        sort(population.begin(), population.end(),
            [](const Individual& a, const Individual& b) {
                return a.fitness > b.fitness;
            });

        while (nextOutputIndex < outputGenerations.size()) {
            cout << population[0].fitness << endl;
            nextOutputIndex++;
        }

        cout << endl;
        cout << population[0].fitness << endl;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int capacity, numItems;
    cin >> capacity >> numItems;

    vector<Item> items(numItems);
    for (int i = 0; i < numItems; i++) {
        cin >> items[i].weight >> items[i].value;
    }

    int popSize = 60;
    int maxGen = 600;

    if (numItems <= 30) {
        popSize = 100;
        maxGen = 1000;
    }
    else if (numItems <= 100) {
        popSize = 70;
        maxGen = 700;
    }
    else if (numItems <= 200) {
        popSize = 50;
        maxGen = 500;
    }
    else {
        popSize = 40;
        maxGen = 400;
    }

    GeneticAlgorithm ga(capacity, numItems, items, popSize, maxGen);
    ga.runEvolution();

    return 0;
}

