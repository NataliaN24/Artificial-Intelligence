#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

class NPuzzle
{
	int tileCount;
	int boardSize;
	int blankIndex;
	vector<int>startState;
	vector<int>goalState;
	vector<pair<int, int>>goalPosition;

	const int moveRow[4] = { -1,1,0,0 };
	const int moveCol[4] = { 0,0,-1,1 };
	const int oppositeMove[4] = { 1,0,3,2 };

public:

	NPuzzle(int N, int I, const vector<int>& inputNumbers)
	{
		tileCount = N;
		boardSize = static_cast<int>(round(sqrt(N + 1)));
		blankIndex = I;
		startState = inputNumbers;
		createGoalState();
		createGoalPosition();
	}

	void createGoalState() {
		int totalCells = tileCount + 1;
		goalState.resize(totalCells);
		int index;
		if (blankIndex == -1) index = totalCells - 1;
		else index = blankIndex;
		int currentTile = 1;
		for (int i = 0; i < totalCells; ++i) {
			if (i == index) goalState[i] = 0;
			else goalState[i] = currentTile++;
		}
	}

	void createGoalPosition()
	{
		int totalCells = tileCount + 1;
		goalPosition.assign(tileCount + 1, { 0,0 });
		for (int i = 0; i < totalCells; i++) {
			int tile = goalState[i];
			int row = i / boardSize;
			int col = i % boardSize;
			goalPosition[tile] = { row,col };
		}
	}

	int getRowFromBottom(int index)const
	{
		return boardSize - index / boardSize;
	}

	long long countInversions(const vector<int>& state)const
	{
		vector<int> seq;
		for (int x : state) {
			if (x != 0) seq.push_back(x);
		}
		long long countInv = 0;
		for (int i = 0; i < (int)seq.size(); ++i) {
			for (int j = i + 1; j < (int)seq.size(); ++j) {
				if (seq[i] > seq[j]) ++countInv;
			}
		}
		return countInv;
	}

	bool hasSolution()const
	{
		long long invStart = countInversions(startState);
		long long invGoal = countInversions(goalState);
		int blankStartIndex = find(startState.begin(), startState.end(), 0) - startState.begin();
		int blankGoalIndex = find(goalState.begin(), goalState.end(), 0) - goalState.begin();
		if (boardSize % 2 == 1)
			return (invStart % 2) == (invGoal % 2);
		return ((invStart + getRowFromBottom(blankStartIndex)) % 2) ==
			((invGoal + getRowFromBottom(blankGoalIndex)) % 2);
	}

	int calculateManhattanDist(const vector<int>& state)const
	{
		int distance = 0;
		for (int i = 0; i < (int)state.size(); ++i) {
			int tile = state[i];
			if (tile == 0) continue;
			int row = i / boardSize;
			int col = i % boardSize;
			distance += abs(row - goalPosition[tile].first) + abs(col - goalPosition[tile].second);
		}
		return distance;
	}

	const char* getDirection(int row, int col)const
	{
		if (row == 0 && col == 1) return "left";
		if (row == 0 && col == -1) return "right";
		if (row == 1 && col == 0) return "up";
		if (row == -1 && col == 0) return "down";
		return "?";
	}

	struct searchRes
	{
		bool solved;
		int nextBox;
	};

	searchRes IDA(vector<int>& state, int blankIdx, int g, int limit, int prevMove, int& heuristic, vector<const char*>& path) const
	{
		int f = g + heuristic;
		if (f > limit) return { false, f };
		if (state == goalState) return { true, f };

		int blankRow = blankIdx / boardSize;
		int blankCol = blankIdx % boardSize;
		int bestNext = INT_MAX;

		for (int move = 0; move < 4; ++move) {
			if (prevMove != -1 && move == oppositeMove[prevMove]) continue;

			int newRow = blankRow + moveRow[move];
			int newCol = blankCol + moveCol[move];

			if (newRow < 0 || newRow >= boardSize || newCol < 0 || newCol >= boardSize) continue;

			int newIndex = newRow * boardSize + newCol;
			int tile = state[newIndex];
			int goalRow = goalPosition[tile].first;
			int goalCol = goalPosition[tile].second;
			int oldDist = abs(newRow - goalRow) + abs(newCol - goalCol);
			int newDist = abs(blankRow - goalRow) + abs(blankCol - goalCol);

			state[blankIdx] = tile;
			state[newIndex] = 0;

			int prevH = heuristic;

			heuristic += (newDist - oldDist);

			path.push_back(getDirection(moveRow[move], moveCol[move]));

			searchRes res = IDA(state, newIndex, g + 1, limit, move, heuristic, path);

			if (res.solved) return res;

			bestNext = min(bestNext, res.nextBox);
			path.pop_back();
			heuristic = prevH;
			state[newIndex] = tile;
			state[blankIdx] = 0;
		}
		return { false, bestNext };
	}

	void solve() const
	{
		if (!hasSolution()) {
			cout << -1 << "\n";
			return;
		}
		vector<int> state = startState;

		int blankIdx = (int)(find(state.begin(), state.end(), 0) - state.begin());
		int heuristic = calculateManhattanDist(state);
		int limit = heuristic;
		vector<const char*> path;

		while (true) {
			searchRes r = IDA(state, blankIdx, 0, limit, -1, heuristic, path);
			if (r.solved) {
				cout << path.size() << "\n";
				for (auto* w : path) cout << w << "\n";
				return;
			}
			if (r.nextBox == INT_MAX) {
				cout << -1 << "\n";
				return;
			}
			limit = r.nextBox;
		}
	}
};

int main() {
	int N;
	int blankIndex;
	cin >> N;
	cin >> blankIndex;
	int total = N + 1;
	int size = static_cast<int>(round(sqrt(total)));
	vector<int> board(total);
	for (int i = 0; i < total; ++i) cin >> board[i];
	NPuzzle puzzle(N, blankIndex, board);
	puzzle.solve();
	return 0;
}
