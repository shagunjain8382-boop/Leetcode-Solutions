class LazySegmentTree {
public:
    int n;
    const long long MOD = 1e9 + 7;

    vector<long long> sum;
    vector<long long> squareSum;
    vector<long long> lazy;

    LazySegmentTree(int n) {
        this->n = n;

        sum.resize(4 * n, 0);
        squareSum.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    void apply(int node, int l, int r, long long val) {

        long long len = r - l + 1;

        squareSum[node] =
            (squareSum[node]
            + 2 * val * sum[node]
            + val * val * len) % MOD;

        sum[node] =
            (sum[node] + val * len) % MOD;

        lazy[node] =
            (lazy[node] + val) % MOD;
    }

    void push(int node, int l, int r) {

        if (lazy[node] == 0 || l == r)
            return;

        int mid = (l + r) / 2;

        apply(node * 2, l, mid, lazy[node]);

        apply(node * 2 + 1, mid + 1, r, lazy[node]);

        lazy[node] = 0;
    }

    void update(int node, int l, int r,
                int ql, int qr) {

        if (qr < l || r < ql)
            return;

        if (ql <= l && r <= qr) {
            apply(node, l, r, 1);
            return;
        }

        push(node, l, r);

        int mid = (l + r) / 2;

        update(node * 2, l, mid, ql, qr);

        update(node * 2 + 1, mid + 1, r, ql, qr);

        sum[node] =
            (sum[node * 2] +
             sum[node * 2 + 1]) % MOD;

        squareSum[node] =
            (squareSum[node * 2] +
             squareSum[node * 2 + 1]) % MOD;
    }

    void update(int l, int r) {
        update(1, 0, n - 1, l, r);
    }

    long long getSquareSum() {
        return squareSum[1];
    }
};

class Solution {
public:

    int sumCounts(vector<int>& nums) {

        int n = nums.size();

        LazySegmentTree tree(n);

        vector<int> last(100001, -1);

        long long ans = 0;

        for (int r = 0; r < n; r++) {

            int x = nums[r];

            int previous = last[x];

            int left = previous + 1;

            tree.update(left, r);

            last[x] = r;

            ans = (ans + tree.getSquareSum()) %
                  1000000007;
        }

        return ans;
    }
};