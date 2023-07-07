// Sum of MSLCM
// UVa ID: 1730
// Verdict: Accepted
// Submission Date: 2023-07-07
// UVa Run Time: 0.010s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    while (cin >> n, n) {
        long long r = 0;
        int L = 1, R, T;
        while (L <= n) {
            T = n / L;
            R = n / T;
            r += 1LL * T * (L + R) * (R - L + 1) / 2;
            L = R + 1;
        }
        cout << r - 1 << '\n';
    }
    return 0;
}
