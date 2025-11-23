https://leetcode.com/problems/number-of-islands/description/
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

 

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.


class Solution {
public:

    void dfs(vector<vector<char>>&grid,int rows,int cols)
    {
        int m=grid.size();
        int n=grid[0].size();
        if(rows<0 || rows>=m || cols<0 || cols>=n || grid[rows][cols]=='0')
        {
            return;
        }
        grid[rows][cols]='0';
        dfs(grid,rows+1,cols);
        dfs(grid,rows-1,cols);
        dfs(grid,rows,cols+1);
        dfs(grid,rows,cols-1);

    }
    int numIslands(vector<vector<char>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        int count=0;
        for(int r=0;r<m;r++)
        {
            for(int c=0;c<n;c++)
            {
                if(grid[r][c]=='1')
                {
                    count++;
                    dfs(grid,r,c);
                }
            }
        }
        return count;
    }
};
