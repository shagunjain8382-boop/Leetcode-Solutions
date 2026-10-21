class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        bool sorted = true;

        // Check if string is already sorted
        for(int i = 1; i < n; i++) {
            if(s[i] < s[i - 1]) {
                sorted = false;
                break;
            }
        }

        if(sorted) {
            return 0;
        }

        // If only 2 characters and not sorted
        if(n == 2) {
            return -1;
        }

        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        // Minimum at first OR maximum at last
        if(s[0] == mn || s[n - 1] == mx) {
            return 1;
        }

        // Minimum or maximum is somewhere in the middle
        for(int i = 1; i < n - 1; i++) {
            if(s[i] == mn || s[i] == mx) {
                return 2;
            }
        }

        return 3;
    }
};