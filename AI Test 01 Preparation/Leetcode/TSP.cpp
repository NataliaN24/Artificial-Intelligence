Fitness for TSP (Total Path Length)

Description:
A chromosome is a permutation of integers 0…N−1 representing a tour.
You must compute the total length of the tour.

Implement:

double fitness(const vector<int>& chrom,
               const vector<pair<double,double>>& coords);


Formula:
distance = sqrt( (x2−x1)² + (y2−y1)² )
Total tour length = sum of distances + return to start.

Fitness definition (minimization):
fitness = 1.0 / totalDistance
(because GA maximizes fitness)

Example:
chrom = {0,1,2}
coords = [(0,0), (0,3), (4,0)]

Distances:
0→1 = 3
1→2 = 5
2→0 = 4
total = 12
fitness = 1/12

Why valid:
This corresponds to the TSP homework in the slides.

#include<iostream>
#include<vector>
#include<queue>
#include <cmath>
using namespace std;

double fitness(const vector<int>& chrom,
    const vector<pair<double, double>>& coords) {

    double total = 0.0;
    for (int i = 0; i < chrom.size()-1; ++i)
    {
     
        double dx = coords[chrom[i]].first - coords[chrom[i + 1]].first;
        double dy = coords[chrom[i]].second - coords[chrom[i + 1]].second;

        total += sqrt(dx * dx + dy * dy);
    }
    double dx = coords[chrom[0]].first - coords[chrom[chrom.size() - 1]].first;
    double dy = coords[chrom[0]].second - coords[chrom[chrom.size() - 1]].second;

    total += sqrt(dx * dx + dy * dy);

    return 1.0 / total;
}

int main()
{
    
    int n;
    cin >> n;
    vector<int> chromosome(n);
    vector<pair<double, double>>coord(n);
    for (int i = 0; i < n; i++)
    {
        cin >> chromosome[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> coord[i].first >> coord[i].second;
    }
   
    cout << fitness(chromosome, coord);
    
}
