// Multi-Peg Towers of Hanoi
// UVa ID: 10444
// Verdict: Accepted
// Submission Date: 2025-11-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// 计算组合数 C(n, k)
long long comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    long long res = 1;
    if (k > n - k) k = n - k;
    for (int i = 1; i <= k; i++) {
        res = res * (n - k + i) / i;
    }
    return res;
}

long long solve(int n, int p) {
    long long moves = 0;
    int k = 0;
    int remaining = n;
    while (remaining > 0) {
        long long count = comb(p - 3 + k, k);
        if (count > remaining) count = remaining;
        moves += count * (1LL << k);  // 2^k
        remaining -= count;
        k++;
    }
    return moves;
}

int main() {
    int n, p;
    int caseNo = 1;
    while (cin >> n >> p) {
        if (n == 0 && p == 0) break;
        long long ans = solve(n, p);
        cout << "Case " << caseNo << ": " << ans << endl;
        caseNo++;
    }
    return 0;
}
