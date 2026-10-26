class Solution {
public:

    long long dfs(vector<vector<int>>& grid, int i, int j) {
        
        int m = grid.size();
        int n = grid[0].size();

        // Out of bounds or water
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0)
            return 0;

        // Store current value
        long long sum = grid[i][j];

        // Mark as visited
        grid[i][j] = 0;

        // 4 directions
        sum += dfs(grid, i + 1, j); // down
        sum += dfs(grid, i - 1, j); // up
        sum += dfs(grid, i, j + 1); // right
        sum += dfs(grid, i, j - 1); // left

        return sum;
    }

    int countIslands(vector<vector<int>>& grid, int k) {

        int m = grid.size();
        int n = grid[0].size();

        int ans = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (grid[i][j] != 0) {

                    long long sum = dfs(grid, i, j);

                    if (sum % k == 0) {
                        ans++;
                    }
                }
            }
        }

        return ans;
    }
};