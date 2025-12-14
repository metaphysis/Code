// How Many Bases
// UVa ID: 12216
// Verdict: Accepted
// Submission Date: 2025-12-06
// UVa Run Time: 0.050s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 100000007;

// 质因数分解
vector<pair<long long, int>> factorize(long long n) {
    vector<pair<long long, int>> factors;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int cnt = 0;
            while (n % p == 0) n /= p, cnt++;
            factors.emplace_back(p, cnt);
        }
    }
    if (n > 1) factors.emplace_back(n, 1);
    return factors;
}

int main() {
    long long N, M, T;
    int caseNo = 1;
    while (cin >> N >> M >> T) {
        if (N == 0 && M == 0 && T == 0) break;
        if (N == 1) { // 没有质因数，无法满足严格条件
            cout << "Case " << caseNo++ << ": " << 0 << endl;
            continue;
        }
        auto factors = factorize(N);
        long long totalGood = 1, totalNonStrict = 1;
        for (auto& [p, exp] : factors) {
            long long a = M * exp;
            long long g = a / T + 1; // |good_p|
            long long n = a / (T + 1) + 1; // |nonstrict_p|
            totalGood = (totalGood * g) % MOD;
            totalNonStrict = (totalNonStrict * n) % MOD;
        }
        long long ans = (totalGood - totalNonStrict) % MOD;
        if (ans < 0) ans += MOD;
        cout << "Case " << caseNo++ << ": " << ans << endl;
    }
    return 0;
}

