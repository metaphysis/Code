// Shrinking Polygons
// UVa ID: 12154
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N && N != 0) {
        vector<int> X(N);
        int S = 0;
        for (int i = 0; i < N; ++i) { cin >> X[i]; S += X[i]; }
        vector<int> pre(N);
        pre[0] = 0;
        for (int i = 1; i < N; ++i) pre[i] = pre[i - 1] + X[i - 1];
        int ans = -1;
        for (int k = N; k >= 3; --k) {
            if (S % k != 0) continue;
            int step = S / k;
            unordered_map<int, int> cnt;
            cnt.reserve(N * 2);
            for (int i = 0; i < N; ++i) {
                int r = pre[i] % step;
                ++cnt[r];
            }
            bool ok = false;
            for (auto &p : cnt) {
                if (p.second == k) { ok = true; break; }
            }
            if (ok) { ans = N - k; break; }
        }
        cout << ans << '\n';
    }
    return 0;
}
