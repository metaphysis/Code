#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int ab, bc, ca;
        cin >> ab >> bc >> ca;
        int val[6] = {100, 50, 20, 10, 5, 1};
        int sum[3] = {0, 0, 0};
        vector<pair<int, int>> coin;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 6; j++) {
                int cnt;
                cin >> cnt;
                sum[i] += cnt * val[j];
                for (int k = 0; k < cnt; k++) coin.push_back({val[j], i});
            }
        }
        int total = sum[0] + sum[1] + sum[2];
        int need[3];
        need[0] = sum[0] - ab + ca;
        need[1] = sum[1] + ab - bc;
        need[2] = sum[2] + bc - ca;
        bool ok = true;
        for (int i = 0; i < 3; i++) if (need[i] < 0 || need[i] > total) ok = false;
        if (!ok) {
            cout << "impossible\n";
            continue;
        }
        vector<int> id = {0, 1, 2};
        sort(id.begin(), id.end(), [&](int x, int y) {
            return need[x] < need[y];
        });
        int limA = need[id[0]], limB = need[id[1]];
        int width = limB + 1;
        const int neg = -1000000000;
        vector<int> dp((limA + 1) * (limB + 1), neg);
        vector<int> ndp((limA + 1) * (limB + 1), neg);
        dp[0] = 0;
        for (auto item : coin) {
            int v = item.first, own = item.second;
            fill(ndp.begin(), ndp.end(), neg);
            for (int a = 0; a <= limA; a++) {
                for (int b = 0; b <= limB; b++) {
                    int pos = a * width + b;
                    if (dp[pos] == neg) continue;
                    ndp[pos] = max(ndp[pos], dp[pos] + (own == id[2]));
                    if (a + v <= limA) {
                        int npos = (a + v) * width + b;
                        ndp[npos] = max(ndp[npos], dp[pos] + (own == id[0]));
                    }
                    if (b + v <= limB) {
                        int npos = a * width + b + v;
                        ndp[npos] = max(ndp[npos], dp[pos] + (own == id[1]));
                    }
                }
            }
            dp.swap(ndp);
        }
        int best = dp[limA * width + limB];
        if (best == neg) cout << "impossible\n";
        else cout << (int)coin.size() - best << '\n';
    }
    return 0;
}
