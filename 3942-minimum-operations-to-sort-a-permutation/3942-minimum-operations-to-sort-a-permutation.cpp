class Solution {
public:

    bool checkIncreasing(vector<int>& nums, int zero, int n) {

        for(int i = 0; i < n; i++) {

            int index = (zero + i) % n;

            if(nums[index] != i) {
                return false;
            }
        }

        return true;
    }

    int minOperations(vector<int>& nums) {

        int n = nums.size();

        int zero = 0;

        // Find original position of 0
        for(int i = 0; i < n; i++) {
            if(nums[i] == 0) {
                zero = i;
                break;
            }
        }

        int originalZero = zero;

        // Check increasing
        bool increasing = checkIncreasing(nums, zero, n);

        if(increasing) {
            return min(
                originalZero,
                n - originalZero + 2
            );
        }

        // Reverse to check decreasing
        reverse(nums.begin(), nums.end());

        zero = n - originalZero - 1;

        bool decreasing = checkIncreasing(nums, zero, n);

        if(decreasing) {
            return min(
                originalZero + 2,
                n - originalZero
            );
        }

        return -1;
    }
};