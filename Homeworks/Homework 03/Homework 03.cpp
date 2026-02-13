#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
#include<chrono>
#include<cstdlib>

using namespace std;

class NQueens {
private:
	int n;
	vector<int> queens;
	vector<int>row;
	vector<int>diagonal1;
	vector<int>diagonal2;

	void initializeBoard()
	{
		fill(row.begin(), row.end(), 0);
		fill(diagonal1.begin(), diagonal1.end(), 0);
		fill(diagonal2.begin(), diagonal2.end(), 0);

		for (int c = 0; c < n; ++c)
		{
			int r = rand() % n;
			queens[c] = r;
			row[r]++;
			diagonal1[c + r]++;
			diagonal2[c - r + n]++;

		}
	}
	int howManyConflicts(int c, int r)const
	{
		return row[r] + diagonal1[c + r] + diagonal2[c - r + n] - 3;
	}

public:
	explicit NQueens(int N) :n(N)
	{
		queens.resize(n);
		row.resize(n);
		diagonal1.resize(2 * n);
		diagonal2.resize(2 * n);
		srand(time(nullptr));
	}
	vector<int>minConflictSolution(int maxSteps = 3000, int maxRestarts = 5)
	{
		if (n == 2 || n == 3)
		{
			return { -1 };
		}

		for (int restart = 0; restart < maxRestarts; ++restart)
		{
			initializeBoard();
			for (int step = 0; step < maxSteps; ++step)
			{
				vector<int>conflictedCols;
				conflictedCols.reserve(n);
				
				for (int c = 0; c < n; c++)
				{
					if (howManyConflicts(c, queens[c]) > 0)
					{
						conflictedCols.push_back(c);
					}
				}
				if (conflictedCols.empty())
				{
					return queens;
				}
				int col = conflictedCols[rand() % conflictedCols.size()];
				int bestRow = queens[col];
				int minConf = INT_MAX;
				for (int r = 0; r < n; ++r)
				{
					int conflict= row[r] + diagonal1[col + r] + diagonal2[col - r + n];
					if (conflict < minConf)
					{
						minConf = conflict;
						bestRow = r;
					}
				}
				int oldRow = queens[col];
				if (oldRow == bestRow)
				{
					continue;
				}
				queens[col] = bestRow;
				row[oldRow]--;
				diagonal1[col + oldRow]--;
				diagonal2[col - oldRow + n]--;
				row[bestRow]++;
				diagonal1[col + bestRow]++;
				diagonal2[col - bestRow + n]++;
			}
		}
		return { -1 };
	}

	void printBoard()const
	{
		for (int row = 0; row < n; ++row)
		{
			for (int col = 0; col < n; ++col)
			{
				cout << (queens[col] == row ? "* " : "_ ");
			}
			cout << "\n";
		}
	}
	void printResult()const
	{
		cout << "[";
		for (int i = 0; i < n; ++i) {
			cout << queens[i];
			if (i + 1 != n)
			{
				cout << ", ";
			}
		}
		cout << "]\n";
	}


};

void runAndMeasure(int n) {
	using namespace chrono;

	auto start = high_resolution_clock::now();

	NQueens solver(n);
	vector<int> solution = solver.minConflictSolution();

	auto end = high_resolution_clock::now();
	long long elapsed_ms = duration_cast<milliseconds>(end - start).count();

	cout << "# TIMES_MS: alg=" << elapsed_ms << "\n";

	if (solution.size() == 1 && solution[0] == -1) {
		cout << -1 << "\n";
		return;
	}

	
		solver.printResult();
		if (n <= 10)
			solver.printBoard();
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	runAndMeasure(n);

	return 0;
}
