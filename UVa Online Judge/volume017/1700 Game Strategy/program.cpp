#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, step;
    while (cin >> n) {
        vector<uint32_t> optMask;
        vector<int> owner;
        for (int i = 0; i < n; i++) {
            cin >> m;
            while (m--) {
                string s;
                uint32_t mask = 0;
                cin >> s;
                for (char c : s)
                    mask |= 1u << (c - 'a');
                optMask.push_back(mask);
                owner.push_back(i);
            }
        }
        vector<vector<int>> ans(n, vector<int>(n, -1));
        vector<uint32_t> cur(n);
        for (int i = 0; i < n; i++) {
            cur[i] = 1u << i;
            ans[i][i] = 0;
        }
        step = 0;
        bool changed = true;
        uint32_t full = (1u << n) - 1;
        while (changed) {
            vector<uint32_t> add(n, 0);
            changed = false;
            step++;
            for (int i = 0; i < (int)optMask.size(); i++) {
                uint32_t mask = optMask[i], can = full;
                while (mask) {
                    int v = __builtin_ctz(mask);
                    can &= cur[v];
                    if (!can) break;
                    mask &= mask - 1;
                }
                add[owner[i]] |= can;
            }
            for (int i = 0; i < n; i++) {
                uint32_t now = add[i] & ~cur[i];
                if (now) {
                    changed = true;
                    cur[i] |= now;
                    while (now) {
                        int j = __builtin_ctz(now);
                        ans[i][j] = step;
                        now &= now - 1;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j) cout << ' ';
                cout << ans[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
}
