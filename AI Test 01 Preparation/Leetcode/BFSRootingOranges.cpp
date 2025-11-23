https://leetcode.com/problems/rotting-oranges/description/
You are given an m x n grid where each cell can have one of three values:

0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

 

Example 1:


Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
Example 2:

Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
Example 3:

Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
class Solution {
public:

    int bfs(queue<pair<int,int>> &q, vector<vector<int>> &grid, int fresh, int m, int n) {
        int minutes = 0;

        vector<pair<int,int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};

        while (!q.empty()) {
            int size = q.size();
            bool infected = false;

            while (size--) {
                auto cell = q.front();
                q.pop();

                int r = cell.first;
                int c = cell.second;

                for (auto &d : dirs) {
                    int nr = r + d.first;
                    int nc = c + d.second;

                    
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;

                    if (grid[nr][nc] == 1) {
                        grid[nr][nc] = 2;   // rot it
                        fresh--;
                        infected = true;
                        q.push({nr, nc});
                    }
                }
            }

            if (infected) minutes++;
        }

        return (fresh == 0 ? minutes : -1);
    }

    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        queue<pair<int,int>> q;
        int fresh = 0;

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == 2) {
                    q.push({r, c});
                } else if (grid[r][c] == 1) {
                    fresh++;
                }
            }
        }

        if (fresh == 0)
            return 0;

        return bfs(q, grid, fresh, m, n);
    }
};
