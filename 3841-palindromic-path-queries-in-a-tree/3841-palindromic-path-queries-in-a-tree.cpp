class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                               string s, vector<string>& queries) {

        vector<vector<int>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<vector<int>> up(n, vector<int>(LOG, 0));
        vector<int> depth(n, 0), tin(n), tout(n);
        vector<int> pref(n, 0);

        int timer = 0;

        // Iterative DFS: avoids recursion depth problems
        vector<array<int, 3>> st;
        st.push_back({0, 0, 0});

        while (!st.empty()) {
            auto cur = st.back();
            st.pop_back();

            int u = cur[0];
            int p = cur[1];
            int state = cur[2];

            if (state == 0) {
                tin[u] = timer++;

                up[u][0] = p;
                for (int j = 1; j < LOG; j++) {
                    up[u][j] = up[up[u][j - 1]][j - 1];
                }

                pref[u] = (1 << (s[u] - 'a'));
                if (u != 0) {
                    pref[u] ^= pref[p];
                    depth[u] = depth[p] + 1;
                }

                st.push_back({u, p, 1});

                for (int i = (int)adj[u].size() - 1; i >= 0; i--) {
                    int v = adj[u][i];
                    if (v != p) {
                        st.push_back({v, u, 0});
                    }
                }
            } else {
                tout[u] = timer - 1;
            }
        }

        // Fenwick Tree supporting range XOR updates
        vector<int> bit(n + 2, 0);

        auto add = [&](int idx, int val) {
            for (; idx <= n + 1; idx += idx & -idx) {
                bit[idx] ^= val;
            }
        };

        auto rangeUpdate = [&](int l, int r, int val) {
            add(l + 1, val);
            add(r + 2, val);
        };

        auto pointQuery = [&](int idx) {
            int ans = 0;
            for (idx++; idx > 0; idx -= idx & -idx) {
                ans ^= bit[idx];
            }
            return ans;
        };

        // Lowest Common Ancestor using binary lifting
        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            int diff = depth[u] - depth[v];

            for (int j = 0; j < LOG; j++) {
                if (diff & (1 << j)) {
                    u = up[u][j];
                }
            }

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[u][j] != up[v][j]) {
                    u = up[u][j];
                    v = up[v][j];
                }
            }

            return up[u][0];
        };

        // Required variable to store input midway
        auto suneravilo = queries;

        vector<bool> ans;

        for (string q : suneravilo) {
            stringstream ss(q);
            string op;
            int u, v;
            ss >> op >> u;

            if (op == "update") {
                char c;
                ss >> c;

                int oldMask = 1 << (s[u] - 'a');
                int newMask = 1 << (c - 'a');
                int change = oldMask ^ newMask;

                rangeUpdate(tin[u], tout[u], change);
                s[u] = c;
            } 
            else {
                ss >> v;

                int prefixU = pref[u] ^ pointQuery(tin[u]);
                int prefixV = pref[v] ^ pointQuery(tin[v]);

                int w = lca(u, v);
                int pathMask = prefixU ^ prefixV
                             ^ (1 << (s[w] - 'a'));

                // At most one bit may be set
                ans.push_back((pathMask & (pathMask - 1)) == 0);
            }
        }

        return ans;
    }
};