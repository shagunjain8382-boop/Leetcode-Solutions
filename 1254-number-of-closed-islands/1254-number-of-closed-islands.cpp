class Solution {
public:

    bool dfs(vector<vector<int>>& grid, int r, int c) {

        // If we go outside the grid,
        // this island touches the boundary.
        if (r < 0 || r >= grid.size() ||
            c < 0 || c >= grid[0].size()) {
            return false;
        }

        // Already water
        if (grid[r][c] == 1) {
            return true;
        }

        // Mark visited
        grid[r][c] = 1;

        bool up = dfs(grid, r - 1, c);
        bool down = dfs(grid, r + 1, c);
        bool left = dfs(grid, r, c - 1);
        bool right = dfs(grid, r, c + 1);

        return up && down && left && right;
    }

    int closedIsland(vector<vector<int>>& grid) {

        int ans = 0;

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {

                if (grid[i][j] == 0) {

                    if (dfs(grid, i, j)) {
                        ans++;
                    }
                }
            }
        }

        return ans;
    }
};