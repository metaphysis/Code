// Ingenious Metro
// UVa ID: 12246
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T, Q;
    while (cin >> T >> Q) {
        if (T == 0 && Q == 0) break;
        vector<long long> t(T);
        for (int i = 0; i < T; ++i) cin >> t[i];
        if (T == 1) {
            long long c = t[0];
            for (int qi = 0; qi < Q; ++qi) {
                if (qi) cout << ' ';
                long long S, D;
                cin >> S >> D;
                if (D == S || D == 2 * c - S) cout << 'Y';
                else cout << 'N';
            }
            cout << '\n';
            continue;
        }
        long long g = 0;
        for (int i = 1; i < T; ++i) {
            long long diff = t[i] - t[0];
            if (diff < 0) diff = -diff;
            g = __gcd(g, diff);
        }
        long long mod = 2 * g;
        long long base = t[0];
        auto norm = [&](long long x) -> long long {
            x %= mod;
            if (x < 0) x += mod;
            return x;
        };
        for (int qi = 0; qi < Q; ++qi) {
            if (qi) cout << ' ';
            long long S, D;
            cin >> S >> D;
            long long sMod = norm(S);
            long long dMod = norm(D);
            long long target1 = sMod;
            long long target2 = norm(2 * base - S);
            if (dMod == target1 || dMod == target2) cout << 'Y';
            else cout << 'N';
        }
        cout << '\n';
    }
    return 0;
}
