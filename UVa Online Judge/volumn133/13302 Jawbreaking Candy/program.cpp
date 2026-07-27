// Jawbreaking Candy
// UVa ID: 13302
// Verdict: Accepted
// Submission Date: 2026-07-27
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163236732

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll L, n, d;
    while (scanf("%lld %lld %lld", &L, &n, &d) == 3) {
        if (L == 0 && n == 0 && d == 0) break;
        ll bestA = 1, bestB = 1; // 暂存最优的 a 和 b
        for (ll b = 1; b <= n; ++b) {
            ll a = (d * b + L - 1) / L; // ceil(d*b/L)
            // 首次或当前 a/b 更小则更新（交叉相乘比较）
            if (b == 1 || a * bestB < bestA * b) {
                bestA = a;
                bestB = b;
            }
        }
        ll num = bestA * L;
        ll den = bestB;
        ll g = __gcd(num, den);
        num /= g;
        den /= g;
        printf("%lld/%lld\n", num, den);
    }
    return 0;
}
