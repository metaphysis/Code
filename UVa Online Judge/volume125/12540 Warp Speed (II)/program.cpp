#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, h;
    if (!(cin >> n >> h)) return 0;
    vector<vector<int>> sw(n, vector<int>(n)), hp(n, vector<int>(h));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> sw[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < h; j++)
            cin >> hp[i][j];
    string line;
    getline(cin, line);
    bool started = false;
    while (getline(cin, line)) {
        stringstream ss(line);
        vector<int> a;
        int x;
        while (ss >> x) a.push_back(x);
        if (a.empty()) {
            if (started) break;
            continue;
        }
        started = true;
        int m = a.size();
        const long long inf = (1LL << 60);
        vector<vector<long long>> dp(m, vector<long long>(n, inf));
        vector<vector<int>> nxt(m, vector<int>(n, -1));
        for (int s = 1; s < n; s++)
            dp[m - 1][s] = hp[s][a[m - 1]] + sw[s][0];
        for (int i = m - 2; i >= 0; i--) {
            for (int s = 1; s < n; s++) {
                long long best = inf;
                int id = -1;
                for (int t = 1; t < n; t++) {
                    long long val = sw[s][t] + dp[i + 1][t];
                    if (val < best) {
                        best = val;
                        id = t;
                    }
                }
                dp[i][s] = hp[s][a[i]] + best;
                nxt[i][s] = id;
            }
        }
        long long ans = inf;
        int cur = -1;
        for (int s = 1; s < n; s++) {
            long long val = sw[0][s] + dp[0][s];
            if (val < ans) {
                ans = val;
                cur = s;
            }
        }
        cout << ans << '\n';
        for (int i = 0; i < m; i++) {
            if (i) cout << ' ';
            cout << cur;
            cur = nxt[i][cur];
        }
        cout << '\n';
    }
    return 0;
}
