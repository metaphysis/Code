// Pairs of Integers
// UVa ID: 1654
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

long long p10[11];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    p10[0] = 1;
    for (int i = 1; i <= 10; ++i) p10[i] = p10[i - 1] * 10;
    int T;
    cin >> T;
    bool firstCase = true;
    while (T--) {
        long long N;
        cin >> N;
        vector<pair<long long, string>> ans;
        for (int k = 2; k <= 10; ++k) {
            for (int p = 0; p < k; ++p) {
                int t = k - 1 - p;
                long long A = p10[t];
                long long maxM = N / A;
                for (long long M = max(0LL, maxM - 3); M <= maxM + 1; ++M) {
                    long long d = M % 11;
                    if (d > 9) continue;
                    long long H = (M - d) / 11;
                    if (p == 0) {
                        if (H != 0 || d < 1 || d > 9) continue;
                    } else {
                        long long lowH = p10[p - 1];
                        long long highH = p10[p] - 1;
                        if (H < lowH || H > highH) continue;
                    }
                    long long remainder = N - M * A;
                    if (remainder < 0 || (remainder & 1)) continue;
                    long long L = remainder / 2;
                    if (L >= A) continue;
                    long long X = (10 * H + d) * A + L;
                    long long Y = H * A + L;
                    if (X + Y != N) continue;
                    if (X < p10[k - 1] || X >= p10[k]) continue;
                    string sx = to_string(X);
                    string sy = to_string(Y);
                    while ((int)sy.size() < k - 1) sy = "0" + sy;
                    ans.push_back({X, sy});
                }
            }
        }
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        if (!firstCase) cout << '\n';
        firstCase = false;
        cout << ans.size() << '\n';
        for (auto &pr : ans) {
            cout << pr.first << " + " << pr.second << " = " << N << '\n';
        }
    }
    return 0;
}
