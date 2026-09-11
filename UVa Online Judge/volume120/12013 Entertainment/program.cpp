// Entertainment
// UVa ID: 12013
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

long double gameWinProb(long double p) {
    long double q = 1.0L - p;
    long double direct = pow(p, 4) * (1.0L + 4.0L * q + 10.0L * q * q);
    long double deuce = 20.0L * pow(p, 3) * pow(q, 3);
    long double winDeuce = p * p / (p * p + q * q);
    return direct + deuce * winDeuce;
}

long double setWinProb(bool maryFirst, long double gS, long double gR) {
    long double dp[7][7] = {};
    for (int mg = 6; mg >= 0; --mg) {
        for (int og = 6; og >= 0; --og) {
            if (mg == 6 && og <= 4) dp[mg][og] = 1.0L;
            else if (og == 6 && mg <= 4) dp[mg][og] = 0.0L;
            else if (mg == 6 && og == 6) {
                long double p1 = maryFirst ? gS : gR;
                long double p2 = maryFirst ? gR : gS;
                long double win2 = p1 * p2;
                long double lose2 = (1.0L - p1) * (1.0L - p2);
                dp[mg][og] = win2 / (win2 + lose2);
            } else {
                bool odd = ((mg + og) % 2 == 0);
                long double cur;
                if (maryFirst) cur = odd ? gS : gR;
                else cur = odd ? gR : gS;
                if (mg == 6 && og == 5) dp[mg][og] = cur + (1.0L - cur) * dp[6][6];
                else if (mg == 5 && og == 6) dp[mg][og] = cur * dp[6][6];
                else dp[mg][og] = cur * dp[mg + 1][og] + (1.0L - cur) * dp[mg][og + 1];
            }
        }
    }
    return dp[0][0];
}

long double matchWinProb(long double s1, long double s2) {
    long double dp[6] = {};
    dp[0] = 1.0L;
    for (int idx = 0; idx < 5; ++idx) {
        long double cur = (idx % 2 == 0) ? s1 : s2;
        long double ndp[6] = {};
        for (int w = 0; w <= idx; ++w) {
            ndp[w] += dp[w] * (1.0L - cur);
            ndp[w + 1] += dp[w] * cur;
        }
        for (int w = 0; w <= 5; ++w) dp[w] = ndp[w];
    }
    long double res = 0.0L;
    for (int w = 3; w <= 5; ++w) res += dp[w];
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int sp, rp;
        cin >> sp >> rp;
        long double pS = sp / 100.0L;
        long double pR = rp / 100.0L;
        long double gS = gameWinProb(pS);
        long double gR = gameWinProb(pR);
        long double s1 = setWinProb(true, gS, gR);
        long double s2 = setWinProb(false, gS, gR);
        long double match = matchWinProb(s1, s2);
        cout << "Case #" << tc << ": " << fixed << setprecision(4) << match * 100.0L << "%\n";
    }
    return 0;
}
