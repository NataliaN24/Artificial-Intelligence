You are given:

a 2D grid representing the puzzle

each tile has a number (0 represents the empty tile)

the goal state has tiles arranged in increasing order:

Example goal state (3×3):
1 2 3
4 5 6
7 8 0

Manhattan distance for the board:

Sum of the Manhattan distances for all tiles except 0.

int manhattanDistance(const vector<vector<int>>& board)
{
    int n = board.size();               // number of rows
    int m = board[0].size();            // number of columns
    int distance = 0;

    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < m; c++)
        {
            int tile = board[r][c];

            if (tile == 0) continue; // ignore the empty tile

            // Goal position for tile:
            int goalRow = (tile - 1) / m;
            int goalCol = (tile - 1) % m;

            // Add Manhattan distance
            distance += abs(r - goalRow) + abs(c - goalCol);
        }
    }

    return distance;
}
int main()
{
    int n;
    cin >> n; // assuming square board n x n

    vector<vector<int>> board(n, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> board[i][j];
        }
    }

    cout << manhattanDistance(board);

    return 0;
}
