// Solve this Equation
// UVa ID: 13196
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.110s

#include <bits/stdc++.h>
using namespace std;

int countSolutions(long long N) {
    if (N < 0) return 0;
    long long n = (long long)sqrt((long double)N);
    while ((n + 1) * (n + 1) <= N) ++n;
    while (n * n > N) --n;
    if (n * n != N) return 0;
    if (N % 36 != 0) return 0;
    long long k = n / 6;
    long long k2 = k * k;
    long long maxA = (long long)(sqrt(5.0L) * k);
    while ((maxA + 1) * (maxA + 1) * 6 <= 30 * k2) ++maxA;
    while (maxA * maxA * 6 > 30 * k2) --maxA;
    long long maxB = (long long)(sqrt(10.0L) * k);
    while ((maxB + 1) * (maxB + 1) * 3 <= 30 * k2) ++maxB;
    while (maxB * maxB * 3 > 30 * k2) --maxB;
    int ans = 0;
    for (long long a = -maxA; a <= maxA; ++a) {
        long long a2 = a * a;
        long long termA = 6 * a2;
        for (long long b = -maxB; b <= maxB; ++b) {
            long long remain = 30 * k2 - termA - 3 * b * b;
            if (remain < 0) continue;
            long long c = (long long)sqrt((long double)remain);
            while ((c + 1) * (c + 1) <= remain) ++c;
            while (c * c > remain) --c;
            if (c * c == remain) {
                if (remain == 0) ans += 1;
                else ans += 2;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long N;
    while (cin >> N) {
        cout << countSolutions(N) << "\n";
    }
    return 0;
}
