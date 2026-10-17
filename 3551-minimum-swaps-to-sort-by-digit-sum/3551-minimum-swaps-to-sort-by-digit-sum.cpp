class Solution {
public:

    int digitSum(int x) {
        int sum = 0;

        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }

        return sum;
    }

    int minSwaps(vector<int>& nums) {

        int n = nums.size();

        vector<int> sorted = nums;

        sort(sorted.begin(), sorted.end(), [&](int a, int b) {

            int sa = digitSum(a);
            int sb = digitSum(b);

            if (sa == sb)
                return a < b;

            return sa < sb;
        });

        unordered_map<int, int> pos;

        for (int i = 0; i < n; i++) {
            pos[nums[i]] = i;
        }

        int swaps = 0;

        for (int i = 0; i < n; i++) {

            if (nums[i] == sorted[i])
                continue;

            int j = pos[sorted[i]];

            swap(nums[i], nums[j]);

            // Update positions after swap
            pos[nums[j]] = j;
            pos[nums[i]] = i;

            swaps++;
        }

        return swaps;
    }
};