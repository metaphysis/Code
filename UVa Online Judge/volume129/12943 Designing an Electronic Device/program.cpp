// Designing an Electronic Device
// UVa ID: 12943
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.270s
// https://blog.csdn.net/metaphysis/article/details/163260453

#include <bits/stdc++.h>
using namespace std;

__int128 gcdFunc(__int128 a, __int128 b);

struct Frac {
    __int128 num, den;
    Frac(__int128 n = 0, __int128 d = 1) { num = n; den = d; reduce(); }
    void reduce() {
        if (den < 0) { num = -num; den = -den; }
        if (num == 0) { den = 1; return; }
        __int128 g = gcdFunc(num < 0 ? -num : num, den);
        num /= g; den /= g;
    }
};

__int128 gcdFunc(__int128 a, __int128 b) {
    while (b) { __int128 t = a % b; a = b; b = t; }
    return a;
}

Frac multiplyFrac(const Frac& a, const Frac& b) {
    return Frac(a.num * b.num, a.den * b.den);
}

bool greaterFrac(const Frac& a, const Frac& b) {
    return a.num * b.den > b.num * a.den;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    while (cin >> N >> K) {
        vector<int> M(N);
        for (int i = 0; i < N; ++i) cin >> M[i];
        vector<vector<pair<int, Frac>>> options(N);
        for (int i = 0; i < N; ++i) {
            options[i].resize(M[i] + 1);
            options[i][0] = make_pair(0, Frac(0, 1));
            for (int m = 1; m <= M[i]; ++m) {
                int alpha, beta, gamma;
                cin >> alpha >> beta >> gamma;
                options[i][m].first = gamma;
                options[i][m].second = Frac(beta - alpha, beta);
            }
        }
        vector<Frac> dp(K + 1, Frac(0, 1));
        dp[0] = Frac(1, 1);
        for (int i = 0; i < N; ++i) {
            vector<Frac> ndp(K + 1, Frac(0, 1));
            for (int c = 0; c <= K; ++c) {
                if (dp[c].num == 0 && dp[c].den == 1) continue;
                for (int m = 0; m <= M[i]; ++m) {
                    int nc = c + options[i][m].first;
                    if (nc > K) continue;
                    Frac newFrac = multiplyFrac(dp[c], options[i][m].second);
                    if (greaterFrac(newFrac, ndp[nc])) ndp[nc] = newFrac;
                }
            }
            dp = move(ndp);
        }
        Frac best(0, 1);
        for (int c = 0; c <= K; ++c)
            if (greaterFrac(dp[c], best)) best = dp[c];
        Frac fail;
        if (best.num == best.den) fail = Frac(0, 1);
        else if (best.num == 0) fail = Frac(1, 1);
        else fail = Frac(best.den - best.num, best.den);
        cout << (long long)fail.num << "/" << (long long)fail.den << "\n";
    }
    return 0;
}
