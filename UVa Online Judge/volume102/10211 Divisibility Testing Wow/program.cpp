// Divisibility Testing Wow
// UVa ID: 10211
// Verdict: Accepted
// Submission Date: 2026-01-11
// UVa Run Time: 0.470s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 快速幂取模
long long modPow(long long base, long long exp, long long mod) {
    long long r = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) r = (r * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return r;
}

int main() {
    int N; cin >> N;
    bool firstCase = true;
    for (int caseIdx = 0; caseIdx < N; caseIdx++) {
        if (!firstCase) cout << endl;
        firstCase = false;
        long long B, D; cin >> B >> D;
        bool found = false;
        // 规则1: Rightmost k
        for (int k = 1; k <= 1000; k++) {
            if (modPow(B, k, D) == 0) {
                cout << "Rightmost " << k << endl;
                found = true;
                break;
            }
        }
        if (found) continue;
        // 规则2: Add all t
        for (int t = 1; t <= 1000; t++) {
            if (modPow(B, t, D) == 1) {
                cout << "Add all " << t << endl;
                found = true;
                break;
            }
        }
        if (found) continue;
        // 规则3: Alternate m change sign
        for (int m = 1; m <= 1000; m++) {
            if (modPow(B, m, D) == D - 1) {
                cout << "Alternate " << m << " change sign" << endl;
                found = true;
                break;
            }
        }
        if (found) continue;
        // 无规则
        cout << "condition not found." << endl;
    }
    return 0;
}
