class Solution {
public:
    const long long MOD = 1000000007;

    long long combination[1001][1001];

    int solve(vector<int>& nums) {
        int n = nums.size();

        if (n <= 2)
            return 1;

        vector<int> left;
        vector<int> right;

        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[0])
                left.push_back(nums[i]);
            else
                right.push_back(nums[i]);
        }

        long long leftWays = solve(left);
        long long rightWays = solve(right);

        long long waysToArrange =
            combination[left.size() + right.size()][left.size()];

        return waysToArrange * leftWays % MOD * rightWays % MOD;
    }

    int numOfWays(vector<int>& nums) {

        int n = nums.size();

        // Calculate nCr
        for (int i = 0; i <= n; i++) {
            combination[i][0] = 1;
            combination[i][i] = 1;

            for (int j = 1; j < i; j++) {
                combination[i][j] =
                    (combination[i - 1][j - 1] +
                     combination[i - 1][j]) % MOD;
            }
        }

        // Original array itself is included,
        // so subtract 1.
        return (solve(nums) - 1 + MOD) % MOD;
    }
};