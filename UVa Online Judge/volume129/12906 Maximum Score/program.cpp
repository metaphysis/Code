// Maximum Score
// UVa ID: 12906
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int p;
        cin >> p;
        vector<pair<int,int>> a(p);
        for (int i = 0; i < p; ++i)
            cin >> a[i].first >> a[i].second;

        sort(a.begin(), a.end());

        ull maxSum = 0;
        ull pref = 0;
        for (int i = 0; i < p; ++i) {
            pref += a[i].second;
            maxSum += (ull)a[i].second * pref;
        }

        long long ways = 1;
        for (int i = 0; i < p - 1; ++i)
            ways = ways * (a[i].second + 1) % MOD;

        cout << "Case " << tc << ": " << maxSum << " " << ways << "\n";
    }
    return 0;
}
