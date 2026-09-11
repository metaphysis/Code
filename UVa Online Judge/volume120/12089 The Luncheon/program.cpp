// The Luncheon
// UVa ID: 12089
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, caseNo = 0;
    while (cin >> n && n) {
        int s; cin >> s;
        vector<int> karim(s);
        for (int i = 0; i < s; ++i) cin >> karim[i];
        int t; cin >> t;
        vector<int> rahim(t);
        for (int i = 0; i < t; ++i) cin >> rahim[i];
        int d; cin >> d;

        bool isKarim[37] = {false};
        for (int i = 0; i < s; ++i) isKarim[karim[i]] = true;
        int A = 0;
        for (int i = 0; i < t; ++i) if (isKarim[rahim[i]]) ++A;
        int B = s - A;
        int C = t - A;
        int neither = n - (A + B + C);

        double p1 = (double)C / n;
        double pMinus1 = (double)A / n;
        double pMinus2 = (double)B / n;
        double p0 = (double)neither / n;

        int offset = 2 * d;
        int range = 3 * d + 1;
        vector<double> dp(range, 0.0), ndp(range, 0.0);
        dp[offset] = 1.0;

        for (int day = 0; day < d; ++day) {
            fill(ndp.begin(), ndp.end(), 0.0);
            for (int idx = 0; idx < range; ++idx) {
                double cur = dp[idx];
                if (cur == 0.0) continue;
                int sum = idx - offset;
                if (idx + 1 < range) ndp[idx + 1] += cur * p1;
                if (idx - 1 >= 0) ndp[idx - 1] += cur * pMinus1;
                if (idx - 2 >= 0) ndp[idx - 2] += cur * pMinus2;
                ndp[idx] += cur * p0;
            }
            dp.swap(ndp);
        }

        double ans = dp[offset];
        if (fabs(ans) < 1e-12) ans = 0.0;
        cout << "Case " << ++caseNo << ": " << fixed << setprecision(5) << ans << "\n";
    }
    return 0;
}
