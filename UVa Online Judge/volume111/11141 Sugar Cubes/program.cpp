#include <bits/stdc++.h>
using namespace std;

const int modVal = 1000000000;

bool canConnect(int mask, int x) {
    for (int i = x; i >= 0; i--)
        if (mask & (1 << (2 * i + 1))) return true;
        else if (mask & (1 << (2 * i))) return false;
    return true;
}

bool isEmpty(int mask, int l, int r) {
    for (int i = l; i <= r; i++)
        if (mask & (3 << (2 * i))) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<vector<pair<int, int>>> edge(n);
        for (int i = 0; i < n; i++) {
            int a[6];
            set<pair<int, int>> st;
            for (int j = 0; j < 6; j++) cin >> a[j];
            for (int j = 0; j < 3; j++) {
                int x = min(a[j], a[5 - j]) - 1, y = max(a[j], a[5 - j]) - 1;
                st.insert({x, y});
            }
            for (pair<int, int> p : st) edge[i].push_back(p);
        }
        vector<int> dp(4096), ndp(4096);
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            ndp = dp;
            for (int mask = 0; mask < 4096; mask++) {
                if (!dp[mask]) continue;
                for (pair<int, int> p : edge[i]) {
                    int x = p.first, y = p.second, newMask = mask;
                    if (!canConnect(mask, x)) continue;
                    if (x == y) {
                        if (!(mask & (1 << (2 * x)))) newMask |= 1 << (2 * x + 1);
                    } else {
                        if (!isEmpty(mask, x + 1, y)) continue;
                        newMask |= 1 << (2 * x);
                        newMask &= ~(1 << (2 * x + 1));
                        newMask |= 1 << (2 * y + 1);
                    }
                    ndp[newMask] += dp[mask];
                    if (ndp[newMask] >= modVal) ndp[newMask] -= modVal;
                }
            }
            dp.swap(ndp);
        }
        int ans = 0;
        for (int mask = 0; mask < 4096; mask++) {
            ans += dp[mask];
            if (ans >= modVal) ans -= modVal;
        }
        ans = (ans - 1 + modVal) % modVal;
        cout << ans << '\n';
    }
    return 0;
}
